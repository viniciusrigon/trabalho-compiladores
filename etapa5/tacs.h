#ifndef	TACS_HEADER
#define TACS_HEADER

#include "hash.h"
#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAC_LABEL 5000
#define TAC_NOP 5001
#define TAC_VEC_IDX 5002
#define TAC_ASS 5003
#define TAC_READ 5004
#define TAC_PRINT_EXP 5005
#define TAC_RETURN 5006
#define TAC_JFALSE 5007
#define TAC_JUMP 5008
#define TAC_REF 5009
#define TAC_ADD 5010
#define TAC_SUB 5011
#define TAC_MUL 5012
#define TAC_DIV 5013
#define TAC_AND 5014
#define TAC_OR 5015
#define TAC_LE 5016
#define TAC_GE 5017
#define TAC_EQ 5018
#define TAC_NE 5019
#define TAC_BT 5020
#define TAC_ST 5021
#define TAC_FUNC_START 5022
#define TAC_FUNC_END   5023
#define TAC_FUNC_CALL 5024
#define TAC_VEC_USE 5025

#define TAC_PRINT_STRING 50050






typedef struct tacNode{
	int type;
	struct tacNode* prev;
	struct tacNode* next;
	hashNode* result;
	hashNode* op1; 
	hashNode* op2;
}tac;


tac* tacJoin(tac* list1, tac* list2);
tac* tacCreate(int type, hashNode* symbol, hashNode* op1, hashNode* op2);
void tacPrint(tac* t1);
tac* tacReverse(tac* tacs);

char* printTypes(int type);

tac* generateCode(ast* node);
tac* generateDecList(ast* node, tac** sonTac);
tac* generateFunDec(ast* node, tac** sonTac);
tac* generateCmdBlk(ast* node, tac** sonTac);
tac* generateCommands(ast* node, tac** sonTac);
tac* generateEmptyCmd(ast* node, tac** sonTac);
tac* generateAss(ast* node, tac** sonTac);
tac* generateRead(ast* node, tac** sonTac);
tac* generatePrint(ast* node, tac** sonTac);
tac* generateReturn(ast* node, tac** sonTac);
tac* generateIf(ast* node, tac** sonTac);
tac* generateIfElse(ast* node, tac** sonTac);
tac* generateWhile(ast* node, tac** sonTac);
tac* generateBinOp(int opCode, ast* node, tac** sonTac);
tac* generateRef(ast* node, tac** sonTac);
tac* generateFunCall(ast* node, tac** sonTac);
tac* generateArgs(ast* node, tac** sonTac);
tac* generateVecUse(ast* node, tac** sonTac);




tac* generateVec(ast* node, tac** sonTac);


#endif
