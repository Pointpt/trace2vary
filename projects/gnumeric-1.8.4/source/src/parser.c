/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     STRING = 258,
     QUOTED_STRING = 259,
     CONSTANT = 260,
     RANGEREF = 261,
     GTE = 262,
     LTE = 263,
     NE = 264,
     AND = 265,
     OR = 266,
     NOT = 267,
     INTERSECT = 268,
     ARG_SEP = 269,
     ARRAY_COL_SEP = 270,
     ARRAY_ROW_SEP = 271,
     SHEET_SEP = 272,
     INVALID_TOKEN = 273,
     PLUS = 274,
     NEG = 275,
     RANGE_INTERSECT = 276,
     RANGE_SEP = 277
   };
#endif
/* Tokens.  */
#define STRING 258
#define QUOTED_STRING 259
#define CONSTANT 260
#define RANGEREF 261
#define GTE 262
#define LTE 263
#define NE 264
#define AND 265
#define OR 266
#define NOT 267
#define INTERSECT 268
#define ARG_SEP 269
#define ARRAY_COL_SEP 270
#define ARRAY_ROW_SEP 271
#define SHEET_SEP 272
#define INVALID_TOKEN 273
#define PLUS 274
#define NEG 275
#define RANGE_INTERSECT 276
#define RANGE_SEP 277




/* Copy the first part of user declarations.  */
#line 1 "parser.y"

/* vim: set sw=8: -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/*
 * Gnumeric Parser
 *
 * (C) 1998-2002 GNOME Foundation
 * (C) 2002-2006 Morten Welinder
 *
 * Authors:
 *    Miguel de Icaza (miguel@gnu.org)
 *    Jody Goldberg (jody@gnome.org)
 *    Morten Welinder (terra@diku.dk)
 *    Almer S. Tigelaar (almer@gnome.org)
 */
#include <gnumeric-config.h>
#include <glib/gi18n-lib.h>
#include "gnumeric.h"
#include "number-match.h"
#include "expr.h"
#include "expr-impl.h"
#include "expr-name.h"
#include "workbook.h"
#include "sheet.h"
#include "gnm-format.h"
#include "application.h"
#include "parse-util.h"
#include "gutils.h"
#include "style.h"
#include "value.h"
#include "str.h"
#include <goffice/utils/go-glib-extras.h>
#include <goffice/app/go-doc.h>
#include <goffice/utils/go-locale.h>

#include <string.h>
#include <errno.h>
#include <stdlib.h>

#define YYDEBUG 1

/* ------------------------------------------------------------------------- */
/* Allocation with disposal-on-error */

/*
 * Defined: the stack itself will be kept in use.  This isn't much, btw.
 *   This setting is good for speed.
 *
 * Not defined: memory will be freed.  The is good for finding leaks in the
 * program.  (Here and elsewhere.)
 */
#define KEEP_DEALLOCATION_STACK_BETWEEN_CALLS

/*
 * If some dork enters "=1+2+2*(1+" we have already allocated space for
 * "1+2", "2", and "1" before the parser sees the syntax error and warps
 * us to the error production in the "line" non-terminal.
 *
 * To make sure we can clean up, we register every allocation.  On success,
 * nothing should be left (except the final expression which is unregistered),
 * but on failure we must free everything allocated.
 *
 * Note: there is some room left for optimisation here.  Talk to terra@diku.dk
 * before you set out to do it.
 */

static void
free_expr_list_list (GSList *list)
{
	GSList *l;
	for (l = list; l; l = l->next)
		gnm_expr_list_unref (l->data);
	g_slist_free (list);
}

typedef void (*ParseDeallocator) (void *);
static GPtrArray *deallocate_stack;

static void
deallocate_init (void)
{
	deallocate_stack = g_ptr_array_new ();
}

static void
deallocate_uninit (void)
{
#ifndef KEEP_DEALLOCATION_STACK_BETWEEN_CALLS
	g_ptr_array_free (deallocate_stack, TRUE);
	deallocate_stack = NULL;
#endif
}

static void
deallocate_all (void)
{
	int i;

	for (i = 0; i < (int)deallocate_stack->len; i += 2) {
		ParseDeallocator freer = g_ptr_array_index (deallocate_stack, i + 1);
		freer (g_ptr_array_index (deallocate_stack, i));
	}

	g_ptr_array_set_size (deallocate_stack, 0);
}

static void
deallocate_assert_empty (void)
{
	if (deallocate_stack->len == 0)
		return;

	g_warning ("deallocate_stack not empty as expected.");
	deallocate_all ();
}

static void *
register_allocation (gpointer data, ParseDeallocator freer)
{
	/* It's handy to be able to register and unregister NULLs.  */
	if (data) {
		int len;
		/*
		 * There are really only a few different freers, so we
		 * could encode the freer in the lower bits of the data
		 * pointer.  Unfortunately, no-one can predict how high
		 * Miguel would jump when he found out.
		 */
		len = deallocate_stack->len;
		g_ptr_array_set_size (deallocate_stack, len + 2);
		g_ptr_array_index (deallocate_stack, len) = data;
		g_ptr_array_index (deallocate_stack, len + 1) = freer;
	}

	/* Returning the pointer here improved readability of the caller.  */
	return data;
}

#define register_expr_allocation(expr) \
  register_allocation ((gpointer)(expr), (ParseDeallocator)&gnm_expr_free)

#define register_expr_list_allocation(list) \
  register_allocation ((list), (ParseDeallocator)&gnm_expr_list_unref)

#define register_expr_list_list_allocation(list) \
  register_allocation ((list), (ParseDeallocator)&free_expr_list_list)

static void
unregister_allocation (void const *data)
{
	int pos;

	/* It's handy to be able to register and unregister NULLs.  */
	if (!data)
		return;

	pos = deallocate_stack->len - 2;
	if (pos >= 0 && data == g_ptr_array_index (deallocate_stack, pos)) {
		g_ptr_array_set_size (deallocate_stack, pos);
		return;
	}

	/*
	 * Bummer.  In certain error cases, it is possible that the parser
	 * will reduce after it has discovered a token that will lead to an
	 * error.  "2/16/1800 00:00" (without the quotes) is an example.
	 * The first "00" is registered before the second division is
	 * reduced.
	 *
	 * This isn't a big deal -- we will just look at the entry just below
	 * the top.
	 */
	pos -= 2;
	if (pos >= 0 && data == g_ptr_array_index (deallocate_stack, pos)) {
		g_ptr_array_index (deallocate_stack, pos) =
			g_ptr_array_index (deallocate_stack, pos + 2);
		g_ptr_array_index (deallocate_stack, pos + 1) =
			g_ptr_array_index (deallocate_stack, pos + 3);

		g_ptr_array_set_size (deallocate_stack, pos + 2);
		return;
	}

	g_warning ("Unbalanced allocation registration");
}

/* ------------------------------------------------------------------------- */

/* Bison/Yacc internals */
static int yylex (void);
static int yyerror (char const *s);

typedef struct {
	char const *ptr;	/* current position of the lexer */
	char const *start;	/* start of the expression */

	/* Location where the parsing is taking place */
	GnmParsePos const *pos;

	/* loaded from convs with locale specific mappings */
	gunichar decimal_point;
	gunichar arg_sep;
	gunichar array_col_sep;
	gunichar array_row_sep;
	/* if arg_sep conflicts with array_col_sep or array_row_sep */
	int in_array_sep_is;	/* token id */

	GnmExprParseFlags     flags;
	GnmConventions const *convs;

	/* dynamic state */
	int in_array; /* toggled in the lexer for '{' and '}' */
	GnmExprList *result;

	GnmParseError *error;
} ParserState;

/* The error returned from the */
static ParserState *state;

static void
report_err (ParserState *state, GError *err,
	    char const *last, int guesstimate_of_length)
{
	if (state->error != NULL) {
		state->error->err    	 = err;
		state->error->end_char   = last - state->start;
		state->error->begin_char = state->error->end_char - guesstimate_of_length;
		if (state->error->begin_char < 0)
			state->error->begin_char = 0;
	} else
		g_error_free (err);
}

/* Handle -cst for use in arrays.  Don't handle other types here.  */
static GnmExpr *
fold_negative_constant (GnmExpr *expr)
{
	if (expr && GNM_EXPR_GET_OPER (expr) == GNM_EXPR_OP_CONSTANT) {
		GnmValue *v = (GnmValue *)expr->constant.value;
		
		if (VALUE_IS_FLOAT (v)) {
			gnm_float f = value_get_as_float (v);
			expr->constant.value = value_new_float (0 - f);
			value_release (v);
			return expr;
		}
	}

	return NULL;
}

/* Handle +cst for use in arrays.  Don't handle other types here.  */
static GnmExpr *
fold_positive_constant (GnmExpr *expr)
{
	if (expr && GNM_EXPR_GET_OPER (expr) == GNM_EXPR_OP_CONSTANT) {
		const GnmValue *v = expr->constant.value;
		if (VALUE_IS_FLOAT (v))
			return expr;
	}

	return NULL;
}

static GnmExpr *
build_unary_op (GnmExprOp op, GnmExpr *expr)
{
	if (!expr) return NULL;

	unregister_allocation (expr);
	return register_expr_allocation (gnm_expr_new_unary (op, expr));
}

static GnmExpr *
build_binop (GnmExpr *l, GnmExprOp op, GnmExpr *r)
{
	if (!l || !r) return NULL;

	unregister_allocation (r);
	unregister_allocation (l);
	return register_expr_allocation (gnm_expr_new_binary (l, op, r));
}

static GnmExpr *
build_logical (GnmExpr *l, gboolean is_and, GnmExpr *r)
{
	static GnmFunc *and_func = NULL, *or_func = NULL;

	if (!l || !r) return NULL;

	if (and_func == NULL)
		and_func = gnm_func_lookup ("AND", NULL);
	if (or_func == NULL)
		or_func = gnm_func_lookup ("OR", NULL);

	unregister_allocation (r);
	unregister_allocation (l);
	return register_expr_allocation
		(gnm_expr_new_funcall2 (is_and ? and_func : or_func, l, r));
}

static GnmExpr *
build_not (GnmExpr *expr)
{
	static GnmFunc *not_func = NULL;

	if (!expr) return NULL;

	if (not_func == NULL)
		not_func = gnm_func_lookup ("NOT", NULL);
	unregister_allocation (expr);
	return register_expr_allocation
		(gnm_expr_new_funcall1 (not_func, expr));
}

/*
 * Build an array expression.
 *
 * Returns NULL on failure.  Caller must YYERROR in that case.
 */
static GnmExpr *
build_array (GSList *cols)
{
	GnmValue *array;
	int mx, y;

	if (!cols) {
		report_err (state, g_error_new (1, PERR_INVALID_EMPTY,
			_("An array must have at least 1 element")),
			state->ptr, 0);
		return NULL;
	}

	mx = g_list_length (cols->data);
	array = value_new_array_empty (mx, g_slist_length (cols));

	y = 0;
	while (cols) {
		GSList *row = cols->data;
		int x = 0;
		while (row && x < mx) {
			GnmExpr const *expr = row->data;
			GnmValue const *v = expr->constant.value;

			g_assert (expr && GNM_EXPR_GET_OPER (expr) == GNM_EXPR_OP_CONSTANT);

			value_array_set (array, x, y, value_dup (v));

			x++;
			row = row->next;
		}
		if (x < mx || row) {
			/* parser_error = PARSE_ERR_SYNTAX; */
			report_err (state, g_error_new (1, PERR_ASYMETRIC_ARRAY,
				_("Arrays must be rectangular")),
				state->ptr, 0);
			value_release (array);
			return NULL;
		}
		y++;
		cols = cols->next;
	}

	return register_expr_allocation (gnm_expr_new_constant (array));
}

/*
 * Build a range constructor.
 *
 * Returns NULL on failure.  Caller must YYERROR in that case.
 */
static GnmExpr *
build_range_ctor (GnmExpr *l, GnmExpr *r, GnmExpr *validate)
{
	if (validate != NULL) {
		if (GNM_EXPR_GET_OPER (validate) != GNM_EXPR_OP_CELLREF ||
		    validate->cellref.ref.sheet != NULL) {
			report_err (state, g_error_new (1, PERR_UNEXPECTED_TOKEN,
				_("Constructed ranges use simple references")),
				state->ptr, 0);
			return NULL;
		    }
	}
	return build_binop (l, GNM_EXPR_OP_RANGE_CTOR, r);
}

/*
 * Build an intersection expression.
 *
 * Returns NULL on failure.  Caller must YYERROR in that case.
 */
static GnmExpr *
build_intersect (GnmExpr *l, GnmExpr *r)
{
	if (!l || !r) return NULL;

	if (gnm_expr_is_rangeref (l) && gnm_expr_is_rangeref (r))
		return build_binop (l, GNM_EXPR_OP_INTERSECT, r);
	report_err (state, g_error_new (1, PERR_SET_CONTENT_MUST_BE_RANGE,
		_("All entries in the set must be references")),
		state->ptr, 0);
	return NULL;
}

/*
 * Build a set expression.
 *
 * Returns NULL on failure.  Caller must YYERROR in that case.
 */
static GnmExpr *
build_set (GnmExprList *list)
{
	/* verify that every thing is a ref */
	GnmExprList *ptr;
	for (ptr = list; ptr != NULL ; ptr = ptr->next) {
		GnmExpr const *expr = ptr->data;
		if (!expr || !gnm_expr_is_rangeref (expr)) {
			report_err (state, g_error_new (1, PERR_SET_CONTENT_MUST_BE_RANGE,
				_("All entries in the set must be references")),
				state->ptr, 0);
			return NULL;
		}
	}

	unregister_allocation (list);
	return register_expr_allocation (gnm_expr_new_set (list));
}

/**
 * parse_string_as_value :
 *
 * Try to parse the entered text as a basic value (empty, bool, int,
 * float, err) if this succeeds, we store this as a GnmValue otherwise, we
 * return a string.
 */
static GnmExpr *
parse_string_as_value (GnmExpr *str)
{
	GnmValue *v = format_match_simple (str->constant.value->v_str.val->str);

	if (v != NULL) {
		unregister_allocation (str);
		gnm_expr_free (str);
		return register_expr_allocation (gnm_expr_new_constant (v));
	}
	return str;
}

/**
 * parser_simple_val_or_name :
 * @str : An expression with oper constant, whose value is a string.
 *
 * Check to see if a string is a simple value or failing that a named
 * expression, if it is not create a placeholder name for it.
 */
static GnmExpr *
parser_simple_val_or_name (GnmExpr *str_expr)
{
	GnmExpr const *res;
	char const *str = str_expr->constant.value->v_str.val->str;
	GnmValue *v = format_match_simple (str);

	/* if it is not a simple value see if it is a name */
	if (v == NULL) {
		GnmNamedExpr *nexpr = expr_name_lookup (state->pos, str);
		if (nexpr == NULL) {
			if (state->flags & GNM_EXPR_PARSE_UNKNOWN_NAMES_ARE_INVALID) {
				report_err (state, g_error_new (1, PERR_UNKNOWN_NAME,
								_("Name '%s' does not exist"),
								str),
					    state->ptr, 0);
				res = NULL;
			} else if (state->flags & GNM_EXPR_PARSE_UNKNOWN_NAMES_ARE_STRINGS) {
				res = gnm_expr_new_constant (value_new_string (str));
			} else {
				GnmParsePos pp = *state->pos;
				pp.sheet = NULL;
				/* Create a place holder */
				nexpr = expr_name_add (&pp, str, NULL, NULL, TRUE, NULL);
				res = gnm_expr_new_name (nexpr, NULL, NULL);
			}
		} else
			res = gnm_expr_new_name (nexpr, NULL, NULL);
	} else
		res = gnm_expr_new_constant (v);

	unregister_allocation (str_expr);
	gnm_expr_free (str_expr);
	return register_expr_allocation (res);
}

static Sheet *
parser_sheet_by_name (Workbook *wb, GnmExpr *name_expr)
{
	char const *name = name_expr->constant.value->v_str.val->str;
	Sheet *sheet = NULL;

	if (wb == NULL)
		return NULL;

	sheet = workbook_sheet_by_name (wb, name);

	/* Applix has absolute and relative sheet references */
	if (sheet == NULL && *name == '$' &&
	    state->convs->allow_absolute_sheet_references)
		sheet = workbook_sheet_by_name (wb, name + 1);

	if (sheet == NULL)
		/* TODO : length is broken in the context of quoted names or
		 * names with escaped character */
		/* -1 is a kludge.  We know that this routine is only called
		 * when the last token was SHEET_SEP */
		report_err (state, g_error_new (1, PERR_UNKNOWN_SHEET,
			_("Unknown sheet '%s'"), name),
			state->ptr-1, strlen (name));

	return sheet;
}

/* Make byacc happier */
int yyparse (void);



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 525 "parser.y"
{
	GnmExpr		*expr;
	GnmValue	*value;
	GnmCellRef	*cell;
	GnmExprList	*list;
	Sheet		*sheet;
	Workbook	*wb;
}
/* Line 187 of yacc.c.  */
#line 673 "parser.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 686 "parser.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   197

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  13
/* YYNRULES -- Number of rules.  */
#define YYNRULES  57
/* YYNRULES -- Number of states.  */
#define YYNSTATES  96

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   277

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    28,    22,     2,
      34,    35,    25,    24,    31,    23,     2,    26,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      19,    21,    20,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    38,     2,    39,    27,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    36,     2,    37,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    29,    30,    32,    33
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     6,     8,    12,    13,    15,    17,    19,
      21,    25,    29,    33,    37,    41,    45,    49,    53,    57,
      61,    65,    69,    73,    77,    81,    84,    87,    90,    93,
      97,   101,   103,   106,   109,   114,   116,   118,   122,   125,
     129,   131,   135,   139,   143,   147,   149,   153,   156,   157,
     159,   162,   165,   167,   168,   170,   174,   176
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      41,     0,    -1,    42,    43,    -1,     1,    -1,    42,    43,
      14,    -1,    -1,     5,    -1,     4,    -1,     3,    -1,    48,
      -1,    43,    24,    43,    -1,    43,    23,    43,    -1,    43,
      25,    43,    -1,    43,    26,    43,    -1,    43,    27,    43,
      -1,    43,    22,    43,    -1,    43,    21,    43,    -1,    43,
      19,    43,    -1,    43,    20,    43,    -1,    43,     7,    43,
      -1,    43,     9,    43,    -1,    43,     8,    43,    -1,    43,
      10,    43,    -1,    43,    11,    43,    -1,    43,    32,    43,
      -1,    23,    43,    -1,    24,    43,    -1,    12,    43,    -1,
      43,    28,    -1,    34,    49,    35,    -1,    36,    52,    37,
      -1,    44,    -1,    47,     3,    -1,    46,     3,    -1,     3,
      34,    49,    35,    -1,     3,    -1,     4,    -1,    38,    45,
      39,    -1,    45,    17,    -1,    46,    45,    17,    -1,     6,
      -1,    44,    33,    44,    -1,     6,    33,    44,    -1,    44,
      33,     6,    -1,     6,    33,     6,    -1,    43,    -1,    43,
      14,    49,    -1,    14,    49,    -1,    -1,     5,    -1,    23,
       5,    -1,    24,     5,    -1,    45,    -1,    -1,    50,    -1,
      50,    15,    51,    -1,    51,    -1,    51,    16,    52,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   553,   553,   559,   567,   573,   576,   577,   578,   582,
     583,   584,   585,   586,   587,   588,   589,   590,   591,   592,
     593,   594,   595,   596,   597,   602,   606,   610,   611,   613,
     631,   638,   639,   657,   678,   695,   696,   699,   731,   740,
     752,   753,   757,   761,   765,   770,   775,   786,   796,   799,
     800,   805,   810,   814,   815,   820,   828,   833
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "STRING", "QUOTED_STRING", "CONSTANT",
  "RANGEREF", "GTE", "LTE", "NE", "AND", "OR", "NOT", "INTERSECT",
  "ARG_SEP", "ARRAY_COL_SEP", "ARRAY_ROW_SEP", "SHEET_SEP",
  "INVALID_TOKEN", "'<'", "'>'", "'='", "'&'", "'-'", "'+'", "'*'", "'/'",
  "'^'", "'%'", "PLUS", "NEG", "','", "RANGE_INTERSECT", "RANGE_SEP",
  "'('", "')'", "'{'", "'}'", "'['", "']'", "$accept", "line", "opt_exp",
  "exp", "function", "string_opt_quote", "workbookref", "sheetref",
  "cellref", "arg_list", "array_exp", "array_row", "array_rows", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,    60,
      62,    61,    38,    45,    43,    42,    47,    94,    37,   274,
     275,    44,   276,   277,    40,    41,   123,   125,    91,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    40,    41,    41,    42,    42,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    44,    45,    45,    46,    47,    47,
      48,    48,    48,    48,    48,    49,    49,    49,    49,    50,
      50,    50,    50,    51,    51,    51,    52,    52
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     3,     0,     1,     1,     1,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     2,     2,     3,
       3,     1,     2,     2,     4,     1,     1,     3,     2,     3,
       1,     3,     3,     3,     3,     1,     3,     2,     0,     1,
       2,     2,     1,     0,     1,     3,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     3,     0,     0,     1,     8,     7,     6,    40,     0,
       0,     0,    48,    53,     0,     2,    31,     0,     0,     0,
       9,    48,     0,    27,    25,    26,    48,    45,     0,    35,
      36,    49,     0,     0,    52,    54,    56,     0,     0,     0,
       0,     0,     0,     0,     4,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    28,     0,     0,    38,    33,     0,
      32,     0,     0,    44,    42,    47,    48,    29,    50,    51,
      53,    53,    30,    37,    19,    21,    20,    22,    23,    17,
      18,    16,    15,    11,    10,    12,    13,    14,    24,    43,
      41,    39,    34,    46,    55,    57
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     3,    27,    16,    17,    18,    19,    20,    28,
      35,    36,    37
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -30
static const yytype_int16 yypact[] =
{
      58,   -30,    17,    99,   -30,     9,     8,   -30,   -29,    99,
      99,    99,    63,   158,    75,   120,    -6,    16,    81,    32,
     -30,    63,    70,     2,     2,     2,    63,   146,    18,   -30,
     -30,   -30,    50,    55,   -30,    59,    49,    53,    52,    99,
      99,    99,    99,    99,   -30,    99,    99,    99,    99,    99,
      99,    99,    99,    99,   -30,    99,    77,   -30,    78,    83,
     -30,    71,    64,   -30,   -30,   -30,    63,   -30,   -30,   -30,
     158,   158,   -30,   -30,    -4,    -4,    -4,    76,    76,    -4,
      -4,    -4,   165,     4,     4,    61,    61,    61,   -30,   -30,
     -30,   -30,   -30,   -30,   -30,   -30
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -30,   -30,   -30,    -1,   -19,   -13,   -30,   -30,   -30,   -10,
     -30,    37,    38
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -37
static const yytype_int8 yytable[] =
{
      34,    38,    15,    64,    22,    59,    42,    43,    23,    24,
      25,    61,    42,    43,    42,    43,    65,     4,    48,    49,
      50,    51,    52,    53,    54,   -36,   -35,    56,    55,    51,
      52,    53,    54,    57,    55,    60,    55,    90,    74,    75,
      76,    77,    78,    21,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    67,    88,    68,    93,    34,    34,     1,
      69,    -5,    -5,    -5,    -5,    71,     5,     6,     7,     8,
      -5,    42,    43,    62,    70,     9,    63,    26,    29,    30,
      62,    -5,    -5,    89,    58,    30,    10,    11,    53,    54,
      72,    73,    -5,    55,    -5,   -35,    -5,    12,    21,    13,
      91,    14,     5,     6,     7,     8,    92,    94,    55,    95,
       0,     9,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    10,    11,     0,     0,     0,    39,    40,    41,
      42,    43,     0,    12,    44,    13,     0,    14,     0,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,     0,
       0,     0,    55,    39,    40,    41,    42,    43,     0,     0,
      66,    29,    30,    31,     0,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    42,    43,     0,    55,     0,
       0,    32,    33,     0,     0,     0,     0,     0,    49,    50,
      51,    52,    53,    54,     0,     0,     0,    55
};

static const yytype_int8 yycheck[] =
{
      13,    14,     3,    22,    33,    18,    10,    11,     9,    10,
      11,    21,    10,    11,    10,    11,    26,     0,    22,    23,
      24,    25,    26,    27,    28,    17,    17,    33,    32,    25,
      26,    27,    28,    17,    32,     3,    32,    56,    39,    40,
      41,    42,    43,    34,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    35,    55,     5,    66,    70,    71,     1,
       5,     3,     4,     5,     6,    16,     3,     4,     5,     6,
      12,    10,    11,     3,    15,    12,     6,    14,     3,     4,
       3,    23,    24,     6,     3,     4,    23,    24,    27,    28,
      37,    39,    34,    32,    36,    17,    38,    34,    34,    36,
      17,    38,     3,     4,     5,     6,    35,    70,    32,    71,
      -1,    12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    23,    24,    -1,    -1,    -1,     7,     8,     9,
      10,    11,    -1,    34,    14,    36,    -1,    38,    -1,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    -1,
      -1,    -1,    32,     7,     8,     9,    10,    11,    -1,    -1,
      14,     3,     4,     5,    -1,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    10,    11,    -1,    32,    -1,
      -1,    23,    24,    -1,    -1,    -1,    -1,    -1,    23,    24,
      25,    26,    27,    28,    -1,    -1,    -1,    32
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,    41,    42,     0,     3,     4,     5,     6,    12,
      23,    24,    34,    36,    38,    43,    44,    45,    46,    47,
      48,    34,    33,    43,    43,    43,    14,    43,    49,     3,
       4,     5,    23,    24,    45,    50,    51,    52,    45,     7,
       8,     9,    10,    11,    14,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    32,    33,    17,     3,    45,
       3,    49,     3,     6,    44,    49,    14,    35,     5,     5,
      15,    16,    37,    39,    43,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    43,    43,    43,     6,
      44,    17,    35,    49,    51,    52
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 553 "parser.y"
    {
		unregister_allocation ((yyvsp[(2) - (2)].expr));
		unregister_allocation ((yyvsp[(1) - (2)].list));
		state->result = gnm_expr_list_prepend ((yyvsp[(1) - (2)].list), (yyvsp[(2) - (2)].expr));
	}
    break;

  case 3:
#line 559 "parser.y"
    {
		if (state->result != NULL) {
			gnm_expr_list_unref (state->result);
			state->result = NULL;
		}
	}
    break;

  case 4:
#line 567 "parser.y"
    {
	       unregister_allocation ((yyvsp[(2) - (3)].expr));
	       unregister_allocation ((yyvsp[(1) - (3)].list));
	       (yyval.list) = gnm_expr_list_prepend ((yyvsp[(1) - (3)].list), (yyvsp[(2) - (3)].expr));
	       register_expr_list_allocation ((yyval.list));
	}
    break;

  case 5:
#line 573 "parser.y"
    { (yyval.list) = NULL; register_expr_list_allocation ((yyval.list)); }
    break;

  case 6:
#line 576 "parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); }
    break;

  case 7:
#line 577 "parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); }
    break;

  case 8:
#line 578 "parser.y"
    {
		(yyval.expr) = parser_simple_val_or_name ((yyvsp[(1) - (1)].expr));
		if ((yyval.expr) == NULL) { YYERROR; }
	}
    break;

  case 9:
#line 582 "parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); }
    break;

  case 10:
#line 583 "parser.y"
    { (yyval.expr) = build_binop ((yyvsp[(1) - (3)].expr), GNM_EXPR_OP_ADD,	(yyvsp[(3) - (3)].expr)); }
    break;

  case 11:
#line 584 "parser.y"
    { (yyval.expr) = build_binop ((yyvsp[(1) - (3)].expr), GNM_EXPR_OP_SUB,	(yyvsp[(3) - (3)].expr)); }
    break;

  case 12:
#line 585 "parser.y"
    { (yyval.expr) = build_binop ((yyvsp[(1) - (3)].expr), GNM_EXPR_OP_MULT,	(yyvsp[(3) - (3)].expr)); }
    break;

  case 13:
#line 586 "parser.y"
    { (yyval.expr) = build_binop ((yyvsp[(1) - (3)].expr), GNM_EXPR_OP_DIV,	(yyvsp[(3) - (3)].expr)); }
    break;

  case 14:
#line 587 "parser.y"
    { (yyval.expr) = build_binop ((yyvsp[(1) - (3)].expr), GNM_EXPR_OP_EXP,	(yyvsp[(3) - (3)].expr)); }
    break;

  case 15:
#line 588 "parser.y"
    { (yyval.expr) = build_binop ((yyvsp[(1) - (3)].expr), GNM_EXPR_OP_CAT,	(yyvsp[(3) - (3)].expr)); }
    break;

  case 16:
#line 589 "parser.y"
    { (yyval.expr) = build_binop ((yyvsp[(1) - (3)].expr), GNM_EXPR_OP_EQUAL,	(yyvsp[(3) - (3)].expr)); }
    break;

  case 17:
#line 590 "parser.y"
    { (yyval.expr) = build_binop ((yyvsp[(1) - (3)].expr), GNM_EXPR_OP_LT,		(yyvsp[(3) - (3)].expr)); }
    break;

  case 18:
#line 591 "parser.y"
    { (yyval.expr) = build_binop ((yyvsp[(1) - (3)].expr), GNM_EXPR_OP_GT,		(yyvsp[(3) - (3)].expr)); }
    break;

  case 19:
#line 592 "parser.y"
    { (yyval.expr) = build_binop ((yyvsp[(1) - (3)].expr), GNM_EXPR_OP_GTE,	(yyvsp[(3) - (3)].expr)); }
    break;

  case 20:
#line 593 "parser.y"
    { (yyval.expr) = build_binop ((yyvsp[(1) - (3)].expr), GNM_EXPR_OP_NOT_EQUAL,	(yyvsp[(3) - (3)].expr)); }
    break;

  case 21:
#line 594 "parser.y"
    { (yyval.expr) = build_binop ((yyvsp[(1) - (3)].expr), GNM_EXPR_OP_LTE,	(yyvsp[(3) - (3)].expr)); }
    break;

  case 22:
#line 595 "parser.y"
    { (yyval.expr) = build_logical ((yyvsp[(1) - (3)].expr), TRUE,	(yyvsp[(3) - (3)].expr)); }
    break;

  case 23:
#line 596 "parser.y"
    { (yyval.expr) = build_logical ((yyvsp[(1) - (3)].expr), FALSE, (yyvsp[(3) - (3)].expr)); }
    break;

  case 24:
#line 597 "parser.y"
    {
		(yyval.expr) = build_intersect ((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
		if ((yyval.expr) == NULL) { YYERROR; }
	}
    break;

  case 25:
#line 602 "parser.y"
    {
		GnmExpr *tmp = fold_negative_constant ((yyvsp[(2) - (2)].expr));
		(yyval.expr) = tmp ? tmp : build_unary_op (GNM_EXPR_OP_UNARY_NEG, (yyvsp[(2) - (2)].expr));
	}
    break;

  case 26:
#line 606 "parser.y"
    {
		/* Don't fold here.  */
		(yyval.expr) = build_unary_op (GNM_EXPR_OP_UNARY_PLUS, (yyvsp[(2) - (2)].expr));
	}
    break;

  case 27:
#line 610 "parser.y"
    { (yyval.expr) = build_not ((yyvsp[(2) - (2)].expr)); }
    break;

  case 28:
#line 611 "parser.y"
    { (yyval.expr) = build_unary_op (GNM_EXPR_OP_PERCENTAGE, (yyvsp[(1) - (2)].expr)); }
    break;

  case 29:
#line 613 "parser.y"
    {
		if ((yyvsp[(2) - (3)].list) == NULL) {
			report_err (state, g_error_new (1, PERR_INVALID_EMPTY,
				_("() is an invalid expression")),
				state->ptr-2, 2);
			YYERROR;
		} else {
			if ((yyvsp[(2) - (3)].list)->next == NULL) {
				unregister_allocation ((yyvsp[(2) - (3)].list));
				(yyval.expr) = register_expr_allocation ((yyvsp[(2) - (3)].list)->data);
				/* NOTE : free list not content */
				gnm_expr_list_free ((yyvsp[(2) - (3)].list));
			} else {
				(yyval.expr) = build_set ((yyvsp[(2) - (3)].list));
				if ((yyval.expr) == NULL) { YYERROR; }
			}
		}
	}
    break;

  case 30:
#line 631 "parser.y"
    {
		unregister_allocation ((yyvsp[(2) - (3)].list));
		(yyval.expr) = build_array ((yyvsp[(2) - (3)].list));
		free_expr_list_list ((yyvsp[(2) - (3)].list));
		if ((yyval.expr) == NULL) { YYERROR; }
	}
    break;

  case 32:
#line 639 "parser.y"
    {
		GnmNamedExpr *nexpr = NULL;
		char const *name = (yyvsp[(2) - (2)].expr)->constant.value->v_str.val->str;
		GnmParsePos pos = *state->pos;

		pos.sheet = (yyvsp[(1) - (2)].sheet);
		nexpr = expr_name_lookup (&pos, name);
		if (nexpr == NULL) {
			report_err (state, g_error_new (1, PERR_UNKNOWN_NAME,
				_("Name '%s' does not exist in sheet '%s'"),
						name, pos.sheet->name_quoted),
				state->ptr, strlen (name));
			YYERROR;
		} else {
			unregister_allocation ((yyvsp[(2) - (2)].expr)); gnm_expr_free ((yyvsp[(2) - (2)].expr));
			(yyval.expr) = register_expr_allocation (gnm_expr_new_name (nexpr, (yyvsp[(1) - (2)].sheet), NULL));
		}
	}
    break;

  case 33:
#line 657 "parser.y"
    {
		GnmNamedExpr *nexpr = NULL;
		char const *name = (yyvsp[(2) - (2)].expr)->constant.value->v_str.val->str;
		GnmParsePos pos = *state->pos;

		pos.sheet = NULL;
		pos.wb = (yyvsp[(1) - (2)].wb);
		nexpr = expr_name_lookup (&pos, name);
		if (nexpr != NULL) {
			unregister_allocation ((yyvsp[(2) - (2)].expr)); gnm_expr_free ((yyvsp[(2) - (2)].expr));
			(yyval.expr) = register_expr_allocation (gnm_expr_new_name (nexpr, NULL, (yyvsp[(1) - (2)].wb)));
		} else {
			report_err (state, g_error_new (1, PERR_UNKNOWN_NAME,
				_("Name '%s' does not exist in sheet '%s'"),
						name, pos.sheet->name_quoted),
				state->ptr, strlen (name));
			YYERROR;
		}
	}
    break;

  case 34:
#line 678 "parser.y"
    {
		char const *name = (yyvsp[(1) - (4)].expr)->constant.value->v_str.val->str;
		GnmExpr const *f_call = (*state->convs->input.func) (
			state->convs, state->pos->wb, name, (yyvsp[(3) - (4)].list));

		(yyval.expr) = NULL;
		if (f_call) {
			/* We're done with the function name.  */
			unregister_allocation ((yyvsp[(1) - (4)].expr)); gnm_expr_free ((yyvsp[(1) - (4)].expr));
			unregister_allocation ((yyvsp[(3) - (4)].list));
			(yyval.expr) = register_expr_allocation (f_call);
		} else {
			YYERROR;
		}
	}
    break;

  case 37:
#line 699 "parser.y"
    {
		char const *wb_name = (yyvsp[(2) - (3)].expr)->constant.value->v_str.val->str;
		Workbook *ref_wb = state->pos
			? (state->pos->wb
			   ? state->pos->wb
			   : (state->pos->sheet
			      ? state->pos->sheet->workbook
			      : NULL))
			: NULL;
		Workbook *wb = gnm_app_workbook_get_by_name
			(wb_name,
			 ref_wb ? go_doc_get_uri ((GODoc *)ref_wb) : NULL);

		if (wb != NULL) {
			unregister_allocation ((yyvsp[(2) - (3)].expr)); gnm_expr_free ((yyvsp[(2) - (3)].expr));
			(yyval.wb) = wb;
		} else {
			/* kludge to produce better error messages
			 * we know that the last token read will be the ']'
			 * so subtract 1.
			 */
			report_err (state, g_error_new (1, PERR_UNKNOWN_WORKBOOK,
				_("Unknown workbook '%s'"), wb_name),
				state->ptr - 1, strlen (wb_name));
			YYERROR;
		}
	}
    break;

  case 38:
#line 731 "parser.y"
    {
		Sheet *sheet = parser_sheet_by_name (state->pos->wb, (yyvsp[(1) - (2)].expr));
		if (sheet != NULL) {
			unregister_allocation ((yyvsp[(1) - (2)].expr)); gnm_expr_free ((yyvsp[(1) - (2)].expr));
			(yyval.sheet) = sheet;
		} else {
			YYERROR;
		}
	}
    break;

  case 39:
#line 740 "parser.y"
    {
		Workbook *wb = (yyvsp[(1) - (3)].wb);
		Sheet *sheet = parser_sheet_by_name (wb, (yyvsp[(2) - (3)].expr));
		if (sheet != NULL) {
			unregister_allocation ((yyvsp[(2) - (3)].expr)); gnm_expr_free ((yyvsp[(2) - (3)].expr));
			(yyval.sheet) = sheet;
		} else {
			YYERROR;
		}
        }
    break;

  case 40:
#line 752 "parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); }
    break;

  case 41:
#line 753 "parser.y"
    {
		(yyval.expr) = build_range_ctor ((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), NULL);
		if ((yyval.expr) == NULL) { YYERROR; }
	}
    break;

  case 42:
#line 757 "parser.y"
    {
		(yyval.expr) = build_range_ctor ((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), (yyvsp[(1) - (3)].expr));
		if ((yyval.expr) == NULL) { YYERROR; }
	}
    break;

  case 43:
#line 761 "parser.y"
    {
		(yyval.expr) = build_range_ctor ((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), (yyvsp[(3) - (3)].expr));
		if ((yyval.expr) == NULL) { YYERROR; }
	}
    break;

  case 44:
#line 765 "parser.y"
    {
		(yyval.expr) = build_binop ((yyvsp[(1) - (3)].expr), GNM_EXPR_OP_RANGE_CTOR, (yyvsp[(3) - (3)].expr));
	}
    break;

  case 45:
#line 770 "parser.y"
    {
		unregister_allocation ((yyvsp[(1) - (1)].expr));
		(yyval.list) = gnm_expr_list_prepend (NULL, (yyvsp[(1) - (1)].expr));
		register_expr_list_allocation ((yyval.list));
        }
    break;

  case 46:
#line 775 "parser.y"
    {
		GSList *tmp = (yyvsp[(3) - (3)].list);
		unregister_allocation ((yyvsp[(3) - (3)].list));
		unregister_allocation ((yyvsp[(1) - (3)].expr));

		if (tmp == NULL)
			tmp = gnm_expr_list_prepend (NULL, gnm_expr_new_constant (value_new_empty ()));

		(yyval.list) = gnm_expr_list_prepend (tmp, (yyvsp[(1) - (3)].expr));
		register_expr_list_allocation ((yyval.list));
	}
    break;

  case 47:
#line 786 "parser.y"
    {
		GSList *tmp = (yyvsp[(2) - (2)].list);
		unregister_allocation ((yyvsp[(2) - (2)].list));

		if (tmp == NULL)
			tmp = gnm_expr_list_prepend (NULL, gnm_expr_new_constant (value_new_empty ()));

		(yyval.list) = gnm_expr_list_prepend (tmp, gnm_expr_new_constant (value_new_empty ()));
		register_expr_list_allocation ((yyval.list));
	}
    break;

  case 48:
#line 796 "parser.y"
    { (yyval.list) = NULL; }
    break;

  case 49:
#line 799 "parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); }
    break;

  case 50:
#line 800 "parser.y"
    {
		GnmExpr *tmp = fold_negative_constant ((yyvsp[(2) - (2)].expr));
		if (!tmp) { YYERROR; }
		(yyval.expr) = tmp;
	 }
    break;

  case 51:
#line 805 "parser.y"
    {
		GnmExpr *tmp = fold_positive_constant ((yyvsp[(2) - (2)].expr));
		if (!tmp) { YYERROR; }
		(yyval.expr) = tmp;
	 }
    break;

  case 52:
#line 810 "parser.y"
    { (yyval.expr) = parse_string_as_value ((yyvsp[(1) - (1)].expr)); }
    break;

  case 53:
#line 814 "parser.y"
    { (yyval.list) = NULL; }
    break;

  case 54:
#line 815 "parser.y"
    {
		unregister_allocation ((yyvsp[(1) - (1)].expr));
		(yyval.list) = g_slist_prepend (NULL, (yyvsp[(1) - (1)].expr));
		register_expr_list_allocation ((yyval.list));
        }
    break;

  case 55:
#line 820 "parser.y"
    {
		unregister_allocation ((yyvsp[(3) - (3)].list));
		unregister_allocation ((yyvsp[(1) - (3)].expr));
		(yyval.list) = g_slist_prepend ((yyvsp[(3) - (3)].list), (yyvsp[(1) - (3)].expr));
		register_expr_list_allocation ((yyval.list));
	}
    break;

  case 56:
#line 828 "parser.y"
    {
		unregister_allocation ((yyvsp[(1) - (1)].list));
		(yyval.list) = g_slist_prepend (NULL, (yyvsp[(1) - (1)].list));
		register_expr_list_list_allocation ((yyval.list));
        }
    break;

  case 57:
#line 833 "parser.y"
    {
		unregister_allocation ((yyvsp[(3) - (3)].list));
		unregister_allocation ((yyvsp[(1) - (3)].list));
		(yyval.list) = g_slist_prepend ((yyvsp[(3) - (3)].list), (yyvsp[(1) - (3)].list));
		register_expr_list_list_allocation ((yyval.list));
	}
    break;


/* Line 1267 of yacc.c.  */
#line 2445 "parser.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 841 "parser.y"


static char const *
find_matching_close (char const *str, char const **res)
{
	while (*str) {
		if (*str == '(') {
			char const *tmp = str;
			str = find_matching_close (str + 1, res);
			if (*str != ')' && *res == NULL) {
				*res = tmp;
				return str;
			}
		} else if (*str == ')')
			return str;
		else if (*str == '\'' || *str == '\"') {
			GString *dummy = g_string_new (NULL);
			char const *end = go_strunescape (dummy, str);
			g_string_free (dummy, TRUE);
			if (end == NULL)
				return str + strlen (str);
			str = end;
			continue; /* skip incrementing str */
		}
		str = g_utf8_next_char (str);
	}

	return str;
}

static inline int
eat_space (ParserState *state, int res)
{
	/* help the user by ignoring pointless spaces after an
	 * arg_sep.  We know they are going to be errors and
	 * the spaces can not be operators in this context */
	while (*state->ptr == ' ')
		state->ptr++;
	return res;
}

/*
 * Do we want to ignore space before a given character?
 */
static gboolean
ignore_space_before (gunichar c)
{
	switch (c) {
	case '*': case '/': case '+': case '-': case '%': case '^': case '&':
	case '>': case '<': case '=':
	case ')':
	case '#':
	case '"': case '\'':  /* Refers to opening quote only.  */
	case UNICODE_LOGICAL_NOT_C:
	case UNICODE_LOGICAL_AND_C:
	case UNICODE_LOGICAL_OR_C:
	case UNICODE_MINUS_SIGN_C:
	case UNICODE_DIVISION_SLASH_C:
	case UNICODE_NOT_EQUAL_TO_C:
	case UNICODE_LESS_THAN_OR_EQUAL_TO_C:
	case UNICODE_GREATER_THAN_OR_EQUAL_TO_C:
	case 0:
		return TRUE;
	default:
		return FALSE;
	}
}

/*
 * Do we want to ignore space after a given character?
 */
static gboolean
ignore_space_after (gunichar c)
{
	switch (c) {
	case '*': case '/': case '+': case '-': case '%': case '^': case '&':
	case '>': case '<': case '=':
	case '(':
	case '"': case '\'':  /* Refers to closing quote only [not actually hit].  */
	case UNICODE_LOGICAL_NOT_C:
	case UNICODE_LOGICAL_AND_C:
	case UNICODE_LOGICAL_OR_C:
	case UNICODE_MINUS_SIGN_C:
	case UNICODE_DIVISION_SLASH_C:
	case UNICODE_NOT_EQUAL_TO_C:
	case UNICODE_LESS_THAN_OR_EQUAL_TO_C:
	case UNICODE_GREATER_THAN_OR_EQUAL_TO_C:
	case 0:
		return TRUE;
	default:
		return FALSE;
	}
}

static int
yylex (void)
{
	gunichar c, tmp;
	char const *start, *end;
	GnmRangeRef ref;
	gboolean is_number = FALSE;
	gboolean is_space = FALSE;
	gboolean error_token = FALSE;

	/*
	 * Some special logic to handle space as intersection char.
	 * Any number of white space characters are treated as one
	 * intersecton.
	 *
	 * Also, if we are not using space for that, drop spaces.
	 */
        while (g_unichar_isspace (g_utf8_get_char (state->ptr))) {
                state->ptr = g_utf8_next_char (state->ptr);
		is_space = TRUE;
	}
	if (is_space && state->convs->intersection_char == ' ' &&
	    !ignore_space_before (g_utf8_get_char (state->ptr)))
		return RANGE_INTERSECT;

	start = state->ptr;
	c = g_utf8_get_char (start);
	if (c == 0)
		return 0;
	state->ptr = g_utf8_next_char (state->ptr);

	if (c == state->convs->intersection_char)
		return RANGE_INTERSECT;

	if (c == '&' && state->convs->decode_ampersands) {
		if (!strncmp (state->ptr, "amp;", 4)) {
			state->ptr += 4;
			return '&';
		}

		if (!strncmp (state->ptr, "lt;", 3)) {
			state->ptr += 3;
			if (*state->ptr == '='){
				state->ptr++;
				return LTE;
			}
			if (!strncmp (state->ptr, "&gt;", 4)) {
				state->ptr += 4;
				return NE;
			}
			return '<';
		}
		if (!strncmp (state->ptr, "gt;", 3)) {
			state->ptr += 3;
			if (*state->ptr == '='){
				state->ptr++;
				return GTE;
			}
			return '>';
		}
		if (!strncmp (state->ptr, "apos;", 5) ||
		    !strncmp (state->ptr, "quot;", 5)) {
			char const *quotes_end;
			char const *p;
			char *string, *s;
			GnmValue *v;

			if (*state->ptr == 'q') {
				quotes_end = "&quot;";
				c = '\"';
			} else {
				quotes_end = "&apos;";
				c = '\'';
			}

			state->ptr += 5;
			p = state->ptr;
			double_quote_loop :
				state->ptr = strstr (state->ptr, quotes_end);
			if (!*state->ptr) {
				report_err (state, g_error_new (1, PERR_MISSING_CLOSING_QUOTE,
								_("Could not find matching closing quote")),
					    p, 1);
				return INVALID_TOKEN;
			}
			if (!strncmp (state->ptr + 6, quotes_end, 6)) {
				state->ptr += 2 * 6;
				goto double_quote_loop;
			}

			s = string = (char *) g_alloca (1 + state->ptr - p);
			while (p != state->ptr) {
				if (*p == '&') {
					if (!strncmp (p, "&amp;", 5)) {
						p += 5;
						*s++ = '&';
						continue;
					} else if (!strncmp (p, "&lt;", 4)) {
						p += 4;
						*s++ = '<';
						continue;
					} else if (!strncmp (p, "&gt;", 4)) {
						p += 4;
						*s++ = '>';
						continue;
					} else if (!strncmp (p, quotes_end, 6)) {
						p += 12; /* two in a row is the escape mechanism */
						*s++ = c;
						continue;
					} else if (!strncmp (p, "&quot;", 6)) {
						p += 6;
						*s++ = '\"';
						continue;
					} else if (!strncmp (p, "&apos;", 6)) {
						p += 6;
						*s++ = '\'';
						continue;
					}
				}
				*s++ = *p++;
			}

			*s = 0;
			state->ptr += 6;

			v = value_new_string (string);
			yylval.expr = register_expr_allocation (gnm_expr_new_constant (v));
			return QUOTED_STRING;
		}
	}

	if (c == ':' && state->convs->range_sep_colon)
		return eat_space (state, RANGE_SEP);

	if (c == state->convs->sheet_name_sep)
		return eat_space (state, SHEET_SEP);

	if (c == '.' && *state->ptr == '.' && state->convs->range_sep_dotdot) {
		state->ptr++;
		return RANGE_SEP;
	}

	if (c == '#' && state->convs->accept_hash_logicals) {
		if (!strncmp (state->ptr, "NOT#", 4)) {
			state->ptr += 4;
			return eat_space (state, NOT);
		}
		if (!strncmp (state->ptr, "AND#", 4)) {
			state->ptr += 4;
			return eat_space (state, AND);
		}
		if (!strncmp (state->ptr, "OR#", 3)) {
			state->ptr += 3;
			return eat_space (state, OR);
		}
	}

	if (c == state->arg_sep)
		return eat_space (state, state->in_array ? state->in_array_sep_is : ARG_SEP);
	if (c == state->array_col_sep)
		return eat_space (state, ARRAY_COL_SEP);
	if (c == state->array_row_sep)
		return eat_space (state, ARRAY_ROW_SEP);

	if (start != (end = state->convs->input.range_ref (&ref, start, state->pos, state->convs))) {
		state->ptr = end;
		if (state->flags & GNM_EXPR_PARSE_FORCE_ABSOLUTE_REFERENCES) {
			if (ref.a.col_relative) {
				ref.a.col += state->pos->eval.col;
				ref.a.col_relative = FALSE;
			}
			if (ref.b.col_relative) {
				ref.b.col += state->pos->eval.col;
				ref.b.col_relative = FALSE;
			}
			if (ref.a.row_relative) {
				ref.a.row += state->pos->eval.row;
				ref.a.row_relative = FALSE;
			}
			if (ref.b.row_relative) {
				ref.b.row += state->pos->eval.row;
				ref.b.row_relative = FALSE;
			}
		} else if (state->flags & GNM_EXPR_PARSE_FORCE_RELATIVE_REFERENCES) {
			if (!ref.a.col_relative) {
				ref.a.col -= state->pos->eval.col;
				ref.a.col_relative = TRUE;
			}
			if (!ref.b.col_relative) {
				ref.b.col -= state->pos->eval.col;
				ref.b.col_relative = TRUE;
			}
			if (!ref.a.row_relative) {
				ref.a.row -= state->pos->eval.row;
				ref.a.row_relative = TRUE;
			}
			if (!ref.b.row_relative) {
				ref.b.row -= state->pos->eval.row;
				ref.b.row_relative = TRUE;
			}
		}

		if (ref.a.sheet == NULL && (state->flags & GNM_EXPR_PARSE_FORCE_EXPLICIT_SHEET_REFERENCES)) {
			ref.a.sheet = state->pos->sheet;
			if (ref.a.sheet == NULL) {
				report_err (state, g_error_new (1, PERR_SHEET_IS_REQUIRED,
					_("Sheet name is required")),
					state->ptr, 0);
				return INVALID_TOKEN;
			}
		}

		if ((ref.b.sheet == NULL || ref.b.sheet == ref.a.sheet) &&
		    ref.a.col		== ref.b.col &&
		    ref.a.col_relative	== ref.b.col_relative &&
		    ref.a.row		== ref.b.row &&
		    ref.a.row_relative	== ref.b.row_relative) {
			yylval.expr = register_expr_allocation (gnm_expr_new_cellref (&ref.a));
			return RANGEREF;
		}
		yylval.expr = register_expr_allocation (gnm_expr_new_constant (
			 value_new_cellrange_unsafe (&ref.a, &ref.b)));
		return RANGEREF;
	}

	/* Do NOT handle negative numbers here.  That has to be done in the
	 * parser otherwise we mishandle A1-1 when it looks like
	 * rangeref CONSTANT  */
	if (c == state->decimal_point) {
		/* Could be a number or a stand alone  */
		if (!g_unichar_isdigit (g_utf8_get_char (state->ptr)))
			return c;
		is_number = TRUE;
	}  else if (g_unichar_isdigit (c)) {
		/* find the end of the first portion of the number */
		do {
			c = g_utf8_get_char (state->ptr);
			state->ptr = g_utf8_next_char (state->ptr);
		} while (g_unichar_isdigit (c));
		is_number = TRUE;
	}

	if (is_number) {
		GnmValue *v = NULL;

		if (c == state->decimal_point || c == 'e' || c == 'E') {
			/* This is float */
			char *end;
			gnm_float d;

			errno = 0;
			d = gnm_strto (start, &end);
			if (start == end) {
				g_warning ("%s is not a double, but was expected to be one", start);
			}  else if (errno != ERANGE) {
				v = value_new_float (d);
				state->ptr = end;
			} else if (c != 'e' && c != 'E') {
				report_err (state, g_error_new (1, PERR_OUT_OF_RANGE,
					_("The number is out of range")),
					state->ptr, end - start);
				return INVALID_TOKEN;
			} else {
				/* For an exponent it's hard to highlight the
				 * right region w/o it turning into an ugly
				 * hack, for now the cursor is put at the end.
				 */
				report_err (state, g_error_new (1, PERR_OUT_OF_RANGE,
					_("The number is out of range")),
					state->ptr, 0);
				return INVALID_TOKEN;
			}
		} else {
			char *end;
			long l;

			errno = 0;
			l = strtol (start, &end, 10);
			if (start == end) {
				g_warning ("%s is not an integer, but was expected to be one", start);
			} else if (errno != ERANGE && l >= INT_MIN && l <= INT_MAX) {
				v = value_new_int (l);
				state->ptr = end;
			} else {
				gnm_float d;

				errno = 0;
				d = gnm_strto (start, &end);
				if (errno != ERANGE) {
					v = value_new_float (d);
					state->ptr = end;
				} else {
					report_err (state, g_error_new (1, PERR_OUT_OF_RANGE,
						_("The number is out of range")),
						state->ptr, end - start);
					return INVALID_TOKEN;
				}
			}
		}

		/* Very odd string,  Could be a bound problem.  Trigger an error */
		if (v == NULL)
			return c;

		yylval.expr = register_expr_allocation (gnm_expr_new_constant (v));
		return CONSTANT;
	}

	switch (c) {
	case '#':
		if (state->ptr[0] != '"') {
			while ((tmp = g_utf8_get_char (state->ptr)) != 0 &&
			       !g_unichar_isspace (tmp)) {
				state->ptr = g_utf8_next_char (state->ptr);
				if (tmp == '!' || tmp == '?' ||
				((state->ptr - start) == 4 && 0 == strncmp (start, "#N/A", 4))) {
					GnmString *name = gnm_string_get_nocopy (g_strndup (start, state->ptr - start));
					yylval.expr = register_expr_allocation
						(gnm_expr_new_constant (
							value_new_error_str (NULL, name)));
					gnm_string_unref (name);
					return CONSTANT;
				}
			}

			report_err (state, g_error_new
				    (1, PERR_UNEXPECTED_TOKEN,
				     _("Improperly formatted error token")),
				    state->ptr, state->ptr - start);

			return INVALID_TOKEN;
		}
		error_token = TRUE;
		start++;
		/* Fall through */
	case '\'':
	case '"': {
		GString *s = g_string_new (NULL);
		char const *end = go_strunescape (s, start);

		if (end == NULL) {
			size_t len = strlen (start);
			g_string_free (s, TRUE);
  			report_err (state,
				    g_error_new (1, PERR_MISSING_CLOSING_QUOTE,
						 _("Could not find matching closing quote")),
				    start + len, len);
			return INVALID_TOKEN;
		}

		state->ptr = (char *)end;

		if (error_token) {
			GnmValue *v = value_new_error (NULL, s->str);
			yylval.expr = register_expr_allocation (gnm_expr_new_constant (v));
			g_string_free (s, TRUE);
			return eat_space (state, CONSTANT);
		} else {
			GnmValue *v = value_new_string_nocopy (g_string_free (s, FALSE));
			yylval.expr = register_expr_allocation (gnm_expr_new_constant (v));
			return eat_space (state, QUOTED_STRING);
		}
	}
	}

	if ((end = state->convs->input.name (start, state->convs))) {
		state->ptr = end;
		yylval.expr = register_expr_allocation (gnm_expr_new_constant (
			value_new_string_nocopy (g_strndup (start, state->ptr - start))));
		return STRING;
	}

	switch (c) {
	case '<':
		if (*state->ptr == '='){
			state->ptr++;
			return eat_space (state, LTE);
		}
		if (*state->ptr == '>'){
			state->ptr++;
			return eat_space (state, NE);
		}
		return eat_space (state, c);

	case '>':
		if (*state->ptr == '='){
			state->ptr++;
			return eat_space (state, GTE);
		}
		return eat_space (state, c);

	case '\n': return 0;

	case '{' :
		state->in_array++;
		return c;
	case '}' :
		state->in_array--;
		return c;

	case UNICODE_LOGICAL_NOT_C: return NOT;
	case UNICODE_MINUS_SIGN_C: return '-';
	case UNICODE_DIVISION_SLASH_C: return '/';
	case UNICODE_LOGICAL_AND_C: return AND;
	case UNICODE_LOGICAL_OR_C: return OR;
	case UNICODE_NOT_EQUAL_TO_C: return eat_space (state, NE);
	case UNICODE_LESS_THAN_OR_EQUAL_TO_C: return eat_space (state, LTE);
	case UNICODE_GREATER_THAN_OR_EQUAL_TO_C: return eat_space (state, GTE);
	}

	if (ignore_space_after (c))
		return eat_space (state, c);
	else
		return c;
}

int
yyerror (char const *s)
{
#if 0
	printf ("Error: %s\n", s);
#endif
	return 0;
}

/**
 * gnm_expr_parse_str:
 *
 * @str   : The string to parse.
 * @pp	  : #GnmParsePos
 * @flags : See parse-utils for descriptions
 * @convs : optionally NULL #GnmConventions
 * @error : optionally NULL ptr to store details of error.
 *
 * Parse a string. if @error is non-null it will be assumed that the
 * caller has passed a pointer to a GnmParseError struct AND that it will
 * take responsibility for freeing that struct and its contents.
 * with parse_error_free.
 * If @convs is NULL use the conventions from @pp.
 **/
GnmExprTop const *
gnm_expr_parse_str (char const *str, GnmParsePos const *pp,
		    GnmExprParseFlags flags,
		    GnmConventions const *convs,
		    GnmParseError *error)
{
	GnmExpr const *expr;
	ParserState pstate;

	g_return_val_if_fail (str != NULL, NULL);
	g_return_val_if_fail (pp != NULL, NULL);

	pstate.start = pstate.ptr = str;
	pstate.pos   = pp;

	pstate.flags		= flags;
	pstate.convs                                    =
		(NULL != convs) ? convs : ((NULL != pp->sheet) ? pp->sheet->convs : gnm_conventions_default);


	pstate.decimal_point = pstate.convs->decimal_sep_dot
		? '.'
		: g_utf8_get_char (go_locale_get_decimal ()->str); /* FIXME: one char handled.  */

	if (pstate.convs->arg_sep != 0)
		pstate.arg_sep = pstate.convs->arg_sep;
	else
		pstate.arg_sep = go_locale_get_arg_sep ();
	if (pstate.convs->array_col_sep != 0)
		pstate.array_col_sep = pstate.convs->array_col_sep;
	else
		pstate.array_col_sep = go_locale_get_col_sep ();
	if (pstate.convs->array_row_sep != 0)
		pstate.array_row_sep = pstate.convs->array_row_sep;
	else
		pstate.array_row_sep = go_locale_get_row_sep ();

	/* Some locales/conventions have ARG_SEP == ARRAY_ROW_SEP
	 * 	eg {1\2\3;4\5\6} for XL style with ',' as a decimal
	 * some have ARG_SEP == ARRAY_COL_SEPARATOR
	 * 	eg {1,2,3;4,5,6} for XL style with '.' as a decimal
	 * 	or {1;2;3|4;5;6} for OOo/
	 * keep track of whether we are in an array to allow the lexer to
	 * dis-ambiguate. */
	if (pstate.arg_sep == pstate.array_col_sep)
		pstate.in_array_sep_is = ARRAY_COL_SEP;
	else if (pstate.arg_sep == pstate.array_row_sep)
		pstate.in_array_sep_is = ARRAY_ROW_SEP;
	else
		pstate.in_array_sep_is = ARG_SEP;
	pstate.in_array = 0;

	pstate.result = NULL;
	pstate.error = error;

	if (deallocate_stack == NULL)
		deallocate_init ();

	g_return_val_if_fail (state == NULL, NULL);

	state = &pstate;
	yyparse ();
	state = NULL;

	if (pstate.result != NULL) {
		deallocate_assert_empty ();

#if 0
		/* If this happens, something is very wrong */
		if (pstate.error != NULL && pstate.error->message != NULL) {
			g_warning ("An error occurred and the GnmExpr is non-null! This should not happen");
			g_warning ("Error message is %s (%d, %d)", pstate.error->message, pstate.error->begin_char,
					pstate.error->end_char);
		}
#endif

		/* Do we have multiple expressions */
		if (pstate.result->next != NULL) {
			if (flags & GNM_EXPR_PARSE_PERMIT_MULTIPLE_EXPRESSIONS)
				expr = gnm_expr_new_set (g_slist_reverse (pstate.result));
			else {
				gnm_expr_list_unref (pstate.result);
				report_err (&pstate, g_error_new (1, PERR_MULTIPLE_EXPRESSIONS,
					_("Multiple expressions are not supported in this context")),
					pstate.start,
					(pstate.ptr - pstate.start));
				expr = NULL;
			}
		} else {
			/* Free the list, do not unref the content */
			expr = pstate.result->data;
			gnm_expr_list_free (pstate.result);
		}
	} else {
		/* If there is no error message, attempt to be more detailed */
		if (pstate.error != NULL &&
		    (pstate.error->err == NULL || pstate.error->err->message == NULL)) {
			char const *last_token = pstate.ptr;

			if (*last_token == '\0') {
				char const *str = pstate.start;
				char const *res = NULL;
				char const *last = find_matching_close (str, &res);

				if (*last)
					report_err (&pstate, g_error_new (1, PERR_MISSING_PAREN_OPEN,
						_("Could not find matching opening parenthesis")),
						last, 1);
				else if (res != NULL)
					report_err (&pstate, g_error_new (1, PERR_MISSING_PAREN_CLOSE,
						_("Could not find matching closing parenthesis")),
						res, 1);
				else
					report_err (&pstate, g_error_new (1, PERR_INVALID_EXPRESSION,
						_("Invalid expression")),
						pstate.ptr, pstate.ptr - pstate.start);
			} else
				report_err (&pstate, g_error_new (1, PERR_UNEXPECTED_TOKEN,
					_("Unexpected token %c"), *last_token),
					last_token, 1);
		}

		deallocate_all ();

		expr = NULL;
	}

	deallocate_uninit ();

	return gnm_expr_top_new (expr);
}

