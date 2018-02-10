/*
 * pln.h: interfaces to read Sheets using a Plan Perfect encoding.
 * Based upon ff-csv.h
 *
 * Kevin Handy <kth@srv.net>
 *
 * $Id: pln.h 13267 2005-02-08 06:32:30Z jody $
 */

#ifndef GNUMERIC_PLN_H
#define GNUMERIC_PLN_H

#include "sheet.h"
#include <goffice/app/go-plugin.h>

PluginInitResult       init_plugin (GOCmdContext *context, PluginData *pd);

#endif /* GNUMERIC_PLN_H */
