#ifndef	HASH_HEADER
#define HASH_HEADER

#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 997
#define SYMBOL_UNDEFINED 0
#define SYMBOL_LIT_INTEGER 1
#define SYMBOL_LIT_TRUE 3
#define SYMBOL_LIT_FALSE 4
#define SYMBOL_LIT_CHAR 5
#define SYMBOL_LIT_STRING 6
#define SYMBOL_IDENTIFIER 7

#define REF_VARIABLE 100
#define REF_VECTOR   101
#define REF_FUNCTION 102
#define REF_LABEL    103

#define DT_UNKNOWN   199
#define DT_INT       200
#define DT_BYTE      201
#define DT_BOOLEAN   202


typedef struct node{
	char* 			text;
	int 			type;
	int				vectorSize;
	int             dataType;
	struct astNode* funDec;
	struct node*	next;
	}hashNode;

int nextTemp;
char hashBuffer[256];


hashNode* hashTable[HASH_SIZE+1];

void hashInit();
void hashPrint();
int hashAddress(char* text);
hashNode* hashFind(char* text, int type);
hashNode* hashInsert(char* text, int type);
hashNode* hashMakeTemp();
hashNode* makeLabel();
hashNode* hashPrintAssembly(FILE* assembly);

void hashSetDataType(int declaredType, hashNode* node);

#endif
