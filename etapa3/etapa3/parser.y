%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "ast.h"

%}

%union {
    hashNode* symbol;
    ast*    ast;
    }

%token KW_INT
%token KW_BYTE
%token KW_IF
%token KW_THEN
%token KW_ELSE
%token KW_WHILE
%token KW_PRINT
%token KW_RETURN
%token KW_READ
%token KW_TRUE
%token KW_FALSE

%token OPERATOR_LE
%token OPERATOR_GE
%token OPERATOR_EQ
%token OPERATOR_NE
%token OPERATOR_AND
%token OPERATOR_OR

%token<symbol> TK_IDENTIFIER
%token<symbol> LIT_INTEGER
%token<symbol> LIT_CHAR
%token<symbol> LIT_STRING

%token TOKEN_ERROR

%type<ast> tipo
%type<ast> program
%type<ast> declarationList
%type<ast> declaration
%type<ast> funcVarBlock
%type<ast> commandBlock
%type<ast> funcVar
%type<ast> funcVarBlockCont
%type<ast> commands
%type<ast> command
%type<ast> assignment                     
%type<ast> read
%type<ast> print
%type<ast> return                        
%type<ast> if                            
%type<ast> while                         
%type<ast> exp                             
%type<ast> args
%type<ast> argsCont

%nonassoc '!'
%left OPERATOR_OR OPERATOR_AND
%left OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_NE '>' '<'
%left '+' '-'
%left '*' '/'

%start program					

%%


program:
    declarationList                     { $$ = $1; forEachDo($$, astPrintSingle); astCreateCode($$); }      
    |                                   { $$ = 0; }
    ;

declarationList:
    declaration declarationList         { $$ = astCreate(AST_DECL,0,$1,$2,0,0); }
    |declaration                        { $$ = astCreate(AST_DECL,0,$1,0,0,0); }
    ;    
   
tipo:
    KW_INT                              { $$ = astCreate(AST_INT,0,0,0,0,0);}
    |KW_BYTE                            { $$ = astCreate(AST_BYTE,0,0,0,0,0);}
    ;
   
declaration:
    tipo TK_IDENTIFIER '[' LIT_INTEGER ']' ';'      { $$ = astCreate(AST_VECTDEC,$2,$1,astCreate(AST_REF,$4,0,0,0,0),0,0);}
    |tipo TK_IDENTIFIER ';'                         { $$ = astCreate(AST_VARDEC,$2,$1,0,0,0); }
    |tipo TK_IDENTIFIER '(' funcVarBlock ')' commandBlock  { $$ = astCreate(AST_FUNDEC,$2,$1,$4,$6,0); }     
    ;
    
funcVarBlock:
    funcVar funcVarBlockCont        { $$ = astCreate(AST_FUNCVAR,0,$1,$2,0,0); }
    |                               { $$ = 0; }
    ;
funcVarBlockCont:
    ',' funcVar funcVarBlockCont    { $$ = astCreate(AST_FUNCVAR,0,$2,$3,0,0); }
    |                               { $$ = 0; }
    ;
funcVar:
    tipo TK_IDENTIFIER              { $$ = astCreate(AST_DECS,$2,$1,0,0,0); }
    ;     

commandBlock:
    '{' commands '}'                { $$ = astCreate(AST_COMBLK,0,$2,0,0,0); }
    ;
    
commands:
    command ';' commands            { $$ = astCreate(AST_COMMANDS,0,$1,$3,0,0); }
    |command                        { $$ = $1; }
    |                               { $$ = 0;  }
    ;
   
command:
    assignment                      { $$ = $1; }
    |read                           { $$ = $1; }
    |print                          { $$ = $1; }
    |return                         { $$ = $1; }
    |if                             { $$ = $1; }
    |while                          { $$ = $1; }
    |commandBlock                   { $$ = $1; }
    |';'                            { $$ = astCreate(AST_EPTCMD,0,0,0,0,0); }
    ;
    
assignment:
    TK_IDENTIFIER '=' exp                   { $$ = astCreate(AST_ASSIGN,$1,$3,0,0,0); }
    |TK_IDENTIFIER '[' exp ']' '=' exp      { $$ = astCreate(AST_ASSIGN,$1,$3,$6,0,0); }       
    ;
    
read:
//    KW_READ TK_IDENTIFIER '[' exp ']'   { $$ = astCreate(AST_READ,$2,$4,0,0,0); }
    KW_READ TK_IDENTIFIER              { $$ = astCreate(AST_READ,$2,0,0,0,0); }
    ;
  
print:
    KW_PRINT LIT_STRING             { $$ = astCreate(AST_PRINT,$2,0,0,0,0); }
    |KW_PRINT exp                   { $$ = astCreate(AST_PRINT,0,$2,0,0,0); }
    ;
    
return:
    KW_RETURN exp                   { $$ = astCreate(AST_RETURN,0,$2,0,0,0); }
    ;      
    
if:
    KW_IF '(' exp ')' KW_THEN command KW_ELSE command   { $$ = astCreate(AST_IFELSE,0,$3,$6,$8,0); }
    |KW_IF '(' exp ')' KW_THEN command                  { $$ = astCreate(AST_IF,0,$3,$6,0,0); }
    ;
            
while:
    KW_WHILE '(' exp ')' command    { $$ = astCreate(AST_WHILE,0,$3,$5,0,0); }
    ;

exp:
    TK_IDENTIFIER                   { $$ = astCreate(AST_REF,$1,0,0,0,0); }
    |TK_IDENTIFIER '['exp']'        { $$ = astCreate(AST_VEC,hashMakeTemp(),astCreate(AST_VEC_USE,$1,$3,0,0,0),0,0,0);}
    |TK_IDENTIFIER '(' args ')'     { $$ = astCreate(AST_FUNC_CALL,hashMakeTemp(),astCreate(AST_FUNC_USE,$1,$3,0,0,0),0,0,0);}
    |LIT_INTEGER                    { $$ = astCreate(AST_REF,$1,0,0,0,0); }
    |'(' exp ')'                    { $$ = $2; }
    |exp '+' exp                    { $$ = astCreate(AST_ADD,hashMakeTemp(),$1,$3,0,0); }
    |exp '-' exp                    { $$ = astCreate(AST_SUB,hashMakeTemp(),$1,$3,0,0); }
    |exp '*' exp                    { $$ = astCreate(AST_MUL,hashMakeTemp(),$1,$3,0,0); }
    |exp '/' exp                    { $$ = astCreate(AST_DIV,hashMakeTemp(),$1,$3,0,0); }
    |exp OPERATOR_LE exp            { $$ = astCreate(AST_LE ,hashMakeTemp(),$1,$3,0,0); }
    |exp OPERATOR_GE exp            { $$ = astCreate(AST_GE ,hashMakeTemp(),$1,$3,0,0); }
    |exp OPERATOR_EQ exp            { $$ = astCreate(AST_EQ ,hashMakeTemp(),$1,$3,0,0); }
    |exp OPERATOR_NE exp            { $$ = astCreate(AST_NE ,hashMakeTemp(),$1,$3,0,0); }
    |exp '>' exp                    { $$ = astCreate(AST_BT ,hashMakeTemp(),$1,$3,0,0); }
    |exp '<' exp                    { $$ = astCreate(AST_ST ,hashMakeTemp(),$1,$3,0,0); }
    |exp OPERATOR_AND exp           { $$ = astCreate(AST_AND,hashMakeTemp(),$1,$3,0,0); }
    |exp OPERATOR_OR exp            { $$ = astCreate(AST_OR ,hashMakeTemp(),$1,$3,0,0); }
    ;  

args:
    exp argsCont                    { $$ = astCreate(AST_ARGS,0,$1,$2,0,0); }
    |                               { $$ = 0; }
    ;
    
argsCont:
    ',' exp argsCont                { $$ = astCreate(AST_ARGS,0,$2,$3,0,0); }
    |                               { $$ = 0; }
    ;

%%

int yyerror(char* error){
	printf("Error at line %d: %s\n",getLineNumber(),error);
	exit(3);
	
}
