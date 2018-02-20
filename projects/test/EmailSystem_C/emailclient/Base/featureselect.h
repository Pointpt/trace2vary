#ifndef FEATURESELECT_H
#define FEATURESELECT_H
/*
 * dummy featureselect
 */

int __SELECTED_FEATURE_Base;

int __SELECTED_FEATURE_Keys;

int __SELECTED_FEATURE_Encrypt;

int __SELECTED_FEATURE_AutoResponder;

int __SELECTED_FEATURE_AddressBook;

int __SELECTED_FEATURE_Sign;

int __SELECTED_FEATURE_Forward;

int __SELECTED_FEATURE_Verify;

int __SELECTED_FEATURE_Decrypt;

int __GUIDSL_ROOT_PRODUCTION;
int __GUIDSL_NON_TERMINAL_main;


int select_one();
void select_features();
void select_helpers();
int valid_product();
#endif
