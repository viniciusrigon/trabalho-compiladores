#ifndef	SEMANTIC_HEADER
#define SEMANTIC_HEADER
#include "hash.h"
#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NO_ERROR        0
#define UNKNOWN         999
#define REDECLARED      1000
#define NOT_DECLARED    1001
#define USE_ERROR       1002
#define DATATYPE_ERROR  1003
#define DATATYPE_WARN   1004
#define ARGUMENT_ERROR  1005


void fullSemanticAnalizis(ast* root);

//functions to perform each part of the semantic verification.
int typeVerification(ast* node);
int undeclaredVerification(ast* node);
int useVerification(ast* node);
void dataTypeDecsVerification(ast* node);
int dataTypeVerification(ast* node);
int argumentsVerification(ast* node);


//auxiliary functions for dataTypeVerification

int checkDataTypeAssign(ast* node);
int checkDataTypePrint(ast* node);
int checkDataTypeReturn(ast* node);
int checkDataTypeRef(ast* node);
int checkDataTypeVecUse(ast* node);
int checkDataTypeFunCall(ast* node);
int checkDataTypeIf(ast* node);
int checkDataTypeArithmetic(ast* node);
int checkDataTypeCompare(ast* node);
int checkDataTypeAndOr(ast* node);
int checkDataTypeArgs(ast* node);


//auxiliary functions for arguments Verification

#endif
