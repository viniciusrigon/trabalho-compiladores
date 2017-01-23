#ifndef	AST_HEADER
#define AST_HEADER

#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define AST_MAX_SONS    4

#define AST_REF         0
#define AST_ADD         1
#define AST_SUB         2
#define AST_MUL         3
#define AST_DIV         4
#define AST_AND         5
#define AST_OR 	        6
#define AST_LE 	        7
#define AST_GE 	        8
#define AST_EQ 	        9
#define AST_NE 	        10
#define AST_BT 	        11
#define AST_ST	        12
#define AST_ARGS        13
#define AST_FUNC_CALL   14
#define AST_WHILE       15
#define AST_IF          16
#define AST_IFELSE      17 
#define AST_RETURN      18
#define AST_PRINT       19
#define AST_READ        20
#define AST_ASSIGN      21
#define AST_EPTCMD      22
#define AST_COMMANDS    23
#define AST_COMBLK      24
#define AST_FUNCVAR     25
#define AST_FUNDEC      26
#define AST_VARDEC      27
#define AST_VECTDEC     28
#define AST_DECS        29
#define AST_VEC         30
#define AST_INT			31
#define AST_BYTE		32
#define AST_VEC_USE		33
#define AST_DECL		34
#define AST_FUNC_USE	35


typedef struct astNode{
	int 		    type;
	int             line;
	int             dataType;
	struct node*	symbol;
	struct astNode* son[AST_MAX_SONS];
	}ast;

extern FILE* outputFile;

ast* astCreate(int type,int line,struct node* symbol,ast* s0,ast* s1,ast* s2,ast* s3);
void astPrintSingle(ast* node);
void forEachDo(ast* astree,void (*fun) (ast* ast));
void astCreateCode(ast* node);

//functions to print specific nodes to the file

void astPrintRef(ast* node); 
void astPrintBinOp(ast* node, char* opSymbol);
void astPrintArgs(ast* node); 
void astPrintFunCall(ast* node);
void astPrintFunUse(ast*node); 
void astPrintWhile(ast* node); 
void astPrintIf(ast* node); 
void astPrintIfElse(ast* node); 
void astPrintReturn(ast* node); 
void astPrintPrint(ast* node); 
void astPrintRead(ast* node);         
void astPrintAss(ast* node);       
void astPrintEmptyCmd(ast* node);       
void astPrintcommands(ast* node);     
void astPrintCmdBlk(ast* node);       
void astPrintFuncVars(ast* node);      
void astPrintFuncDec(ast* node);       
void astPrintVarDec(ast* node); 
void astPrintVectDec(ast* node);       
void astPrintDecs(ast* node);
void astPrintRefVec(ast* node);
void astPrintFunc(ast* node); 
void astPrintVec(ast* node); 
void astPrintDecl(ast* node);

#endif
