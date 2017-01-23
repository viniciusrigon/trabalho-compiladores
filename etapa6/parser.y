%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "ast.h"
#include "semantic.h"
#include "tacs.h"
#include "assembler.h"

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
    declarationList                     { tac* res=0;
                                          $$ = $1; 
                                          //astCreateCode($$); 
                                          fullSemanticAnalizis($$); 
                                          res=generateCode($$);
                                          res=tacReverse(res);
                                          tacPrint(res);
                                          assembler(res); 
                                        }      
    |                                   { $$ = 0; }
    ;

declarationList:
    declaration declarationList         { $$ = astCreate(AST_DECL,getLineNumber(),0,$1,$2,0,0); }
    |declaration                        { $$ = astCreate(AST_DECL,getLineNumber(),0,$1,0,0,0); }
    ;    
   
tipo:
    KW_INT                              { $$ = astCreate(AST_INT,getLineNumber(),0,0,0,0,0);}
    |KW_BYTE                            { $$ = astCreate(AST_BYTE,getLineNumber(),0,0,0,0,0);}
    ;
   
declaration:
    tipo TK_IDENTIFIER '[' LIT_INTEGER ']' ';'  { $$ = astCreate(AST_VECTDEC,getLineNumber(),$2,$1,astCreate(AST_REF,getLineNumber(),$4,0,0,0,0),0,0);$2->vectorSize = atoi($4->text); }
    |tipo TK_IDENTIFIER ';'                               {$$ = astCreate(AST_VARDEC,getLineNumber(),$2,$1,0,0,0); }
    |tipo TK_IDENTIFIER '(' funcVarBlock ')' commandBlock {$$ = astCreate(AST_FUNDEC,getLineNumber(),$2,$1,$4,$6,0);$2->funDec=$$;}     
    ;
    
funcVarBlock:
    funcVar funcVarBlockCont        { $$ = astCreate(AST_FUNCVAR,getLineNumber(),0,$1,$2,0,0); }
    |                               { $$ = 0; }
    ;
funcVarBlockCont:
    ',' funcVar funcVarBlockCont    { $$ = astCreate(AST_FUNCVAR,getLineNumber(),0,$2,$3,0,0); }
    |                               { $$ = 0; }
    ;
funcVar:
    tipo TK_IDENTIFIER              { $$ = astCreate(AST_DECS,getLineNumber(),$2,$1,0,0,0); }
    ;     

commandBlock:
    '{' commands '}'                { $$ = astCreate(AST_COMBLK,getLineNumber(),0,$2,0,0,0); }
    ;
    
commands:
    command ';' commands            { $$ = astCreate(AST_COMMANDS,getLineNumber(),0,$1,$3,0,0); }
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
    |';'                            { $$ = astCreate(AST_EPTCMD,getLineNumber(),0,0,0,0,0); }
    ;
    
assignment:
    TK_IDENTIFIER '=' exp                   { $$ = astCreate(AST_ASSIGN,getLineNumber(),$1,$3,0,0,0); }
    |TK_IDENTIFIER '[' exp ']' '=' exp      { $$ = astCreate(AST_ASSIGN,getLineNumber(),$1,$3,$6,0,0); }       
    ;
    
read:
    KW_READ TK_IDENTIFIER              { $$ = astCreate(AST_READ,getLineNumber(),$2,0,0,0,0); }
    ;
  
print:
    KW_PRINT LIT_STRING             { $$ = astCreate(AST_PRINT,getLineNumber(),$2,0,0,0,0); }
    |KW_PRINT exp                   { $$ = astCreate(AST_PRINT,getLineNumber(),0,$2,0,0,0); }
    ;
    
return:
    KW_RETURN exp                   { $$ = astCreate(AST_RETURN,getLineNumber(),0,$2,0,0,0); }
    ;      
    
if:
    KW_IF '(' exp ')' KW_THEN command KW_ELSE command   { $$ = astCreate(AST_IFELSE,getLineNumber(),0,$3,$6,$8,0); }
    |KW_IF '(' exp ')' KW_THEN command                  { $$ = astCreate(AST_IF,getLineNumber(),0,$3,$6,0,0); }
    ;
            
while:
    KW_WHILE '(' exp ')' command    { $$ = astCreate(AST_WHILE,getLineNumber(),0,$3,$5,0,0); }
    ;

exp:
    TK_IDENTIFIER                   { $$ = astCreate(AST_REF,getLineNumber(),$1,0,0,0,0); }
    |TK_IDENTIFIER '['exp']'        { $$ = astCreate(AST_VEC_USE,getLineNumber(),$1,$3,0,0,0);}
    |TK_IDENTIFIER '(' args ')'     { $$ = astCreate(AST_FUNC_CALL,getLineNumber(),$1,$3,0,0,0);}
    |LIT_INTEGER                    { $$ = astCreate(AST_REF,getLineNumber(),$1,0,0,0,0); }
    |'(' exp ')'                    { $$ = $2; }
    |exp '+' exp                    { $$ = astCreate(AST_ADD,getLineNumber(),hashMakeTemp(),$1,$3,0,0); }
    |exp '-' exp                    { $$ = astCreate(AST_SUB,getLineNumber(),hashMakeTemp(),$1,$3,0,0); }
    |exp '*' exp                    { $$ = astCreate(AST_MUL,getLineNumber(),hashMakeTemp(),$1,$3,0,0); }
    |exp '/' exp                    { $$ = astCreate(AST_DIV,getLineNumber(),hashMakeTemp(),$1,$3,0,0); }
    |exp OPERATOR_LE exp            { $$ = astCreate(AST_LE ,getLineNumber(),hashMakeTemp(),$1,$3,0,0); }
    |exp OPERATOR_GE exp            { $$ = astCreate(AST_GE ,getLineNumber(),hashMakeTemp(),$1,$3,0,0); }
    |exp OPERATOR_EQ exp            { $$ = astCreate(AST_EQ ,getLineNumber(),hashMakeTemp(),$1,$3,0,0); }
    |exp OPERATOR_NE exp            { $$ = astCreate(AST_NE ,getLineNumber(),hashMakeTemp(),$1,$3,0,0); }
    |exp '>' exp                    { $$ = astCreate(AST_BT ,getLineNumber(),hashMakeTemp(),$1,$3,0,0); }
    |exp '<' exp                    { $$ = astCreate(AST_ST ,getLineNumber(),hashMakeTemp(),$1,$3,0,0); }
    |exp OPERATOR_AND exp           { $$ = astCreate(AST_AND,getLineNumber(),hashMakeTemp(),$1,$3,0,0); }
    |exp OPERATOR_OR exp            { $$ = astCreate(AST_OR ,getLineNumber(),hashMakeTemp(),$1,$3,0,0); }
    ;  

args:
    exp argsCont                    { $$ = astCreate(AST_ARGS,getLineNumber(),0,$1,$2,0,0); }
    |                               { $$ = 0; }
    ;
    
argsCont:
    ',' exp argsCont                { $$ = astCreate(AST_ARGS,getLineNumber(),0,$2,$3,0,0); }
    |                               { $$ = 0; }
    ;

%%

int yyerror(char* error){
	printf("Error at line %d: %s\n",getLineNumber(),error);
	exit(3);
	
}

