#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#include <stdlib.h>
#include <string.h>

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20090221

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
#ifdef YYPARSE_PARAM_TYPE
#define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
#else
#define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
#endif
#else
#define YYPARSE_DECL() yyparse(void)
#endif /* YYPARSE_PARAM */

extern int YYPARSE_DECL();

static int yygrowstack(void);
#define YYPREFIX "yy"
#line 2 "parser.y"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "ast.h"

#line 10 "parser.y"
typedef union {
    hashNode* symbol;
    ast*    ast;
    } YYSTYPE;
#line 46 "y.tab.c"
#define KW_INT 257
#define KW_BYTE 258
#define KW_IF 259
#define KW_THEN 260
#define KW_ELSE 261
#define KW_WHILE 262
#define KW_PRINT 263
#define KW_RETURN 264
#define KW_READ 265
#define KW_TRUE 266
#define KW_FALSE 267
#define OPERATOR_LE 268
#define OPERATOR_GE 269
#define OPERATOR_EQ 270
#define OPERATOR_NE 271
#define OPERATOR_AND 272
#define OPERATOR_OR 273
#define TK_IDENTIFIER 274
#define LIT_INTEGER 275
#define LIT_CHAR 276
#define LIT_STRING 277
#define TOKEN_ERROR 278
#define YYERRCODE 256
static const short yylhs[] = {                           -1,
    0,    0,    2,    2,    1,    1,    3,    3,    3,    4,
    4,    7,    7,    6,    5,    8,    8,    8,    9,    9,
    9,    9,    9,    9,    9,    9,   10,   10,   11,   12,
   12,   13,   14,   14,   15,   16,   16,   16,   16,   16,
   16,   16,   16,   16,   16,   16,   16,   16,   16,   16,
   16,   16,   17,   17,   18,   18,
};
static const short yylen[] = {                            2,
    1,    0,    2,    1,    1,    1,    6,    3,    6,    2,
    0,    3,    0,    2,    3,    3,    1,    0,    1,    1,
    1,    1,    1,    1,    1,    1,    3,    6,    2,    2,
    2,    2,    8,    6,    5,    1,    4,    4,    1,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    2,    0,    3,    0,
};
static const short yydefred[] = {                         0,
    5,    6,    0,    0,    1,    0,    0,    3,    0,    8,
    0,    0,    0,    0,    0,    0,   14,    0,    0,   10,
    7,    0,    9,    0,    0,    0,    0,    0,    0,    0,
   26,   25,    0,    0,   19,   20,   21,   22,   23,   24,
   12,    0,    0,    0,   39,   30,    0,    0,    0,   29,
    0,    0,   15,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   16,    0,    0,    0,    0,    0,   40,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   43,   44,    0,    0,   35,   37,    0,   53,   38,    0,
    0,    0,    0,    0,   55,   33,
};
static const short yydgoto[] = {                          3,
    4,    5,    6,   14,   32,   15,   20,   33,   34,   35,
   36,   37,   38,   39,   40,   48,   79,   98,
};
static const short yysindex[] = {                      -234,
    0,    0,    0, -266,    0, -234,  -38,    0, -250,    0,
 -234,  -66, -241,   -5,   -7,  -21,    0,  -77, -234,    0,
    0,  103,    0,   -7,    8,    9,  -40,  -36, -223,  -56,
    0,    0,  -69,    2,    0,    0,    0,    0,    0,    0,
    0,  -36,  -36,  -37,    0,    0,  -36,  347,  347,    0,
  -36,  -36,    0,  103,  101,  110,  -36,  -36,  133,  -36,
  -36,  -36,  -36,  -36,  -36,  -36,  -36,  -36,  -36,  -36,
  -36,  159,  347,    0, -201,  103,  167,  298,   21,    0,
   47,   47,   47,   47,  399,  399,   47,   47,  -35,  -35,
    0,    0,    3,  103,    0,    0,  -36,    0,    0,  -36,
 -198,  298,  347,  103,    0,    0,
};
static const short yyrindex[] = {                        68,
    0,    0,    0,    0,    0,   74,    0,    0,    0,    0,
   35,    0,    0,    0,   38,    0,    0,    0,    0,    0,
    0,  -44,    0,   38,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  -43,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  -28,    0,    0,    0,  -53,  -50,    0,
    0,    0,    0,  -44,    0,    0,    0,   54,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  -48,    0,    0,    0,    0,   59,    0,    0,
   11,   25,   39,   52,  124,  138,   65,   78,  -15,   -2,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  -58,   59,  -39,    0,    0,    0,
};
static const short yygindex[] = {                         0,
   -1,   82,    0,    0,   84,   86,   79,   53,  -54,    0,
    0,    0,    0,    0,    0,  405,    0,    6,
};
#define YYTABLESIZE 670
static const short yytable[] = {                         47,
   34,   11,   58,   47,   52,   31,   70,    7,   32,   13,
   27,   71,   36,   36,   36,   36,   36,   13,   36,   28,
   10,   95,    1,    2,   12,   41,   16,   41,   41,   41,
   36,   36,   17,   36,   51,   18,   19,   21,   42,  101,
   42,   42,   42,   41,   41,   22,   41,   42,   43,  106,
   50,   45,    9,   57,   45,   53,   42,   42,   94,   42,
   54,   99,  104,  100,   36,   46,   34,    2,   46,   45,
   45,   31,   45,    4,   32,   11,   27,   41,   13,   47,
   18,   17,   47,   46,   46,   28,   46,    8,   70,   68,
   42,   69,   48,   71,   54,   48,   36,   47,   47,   56,
   47,   23,   41,   45,   24,   49,   74,  105,   49,   41,
   48,   48,    0,   48,    0,    0,    0,   46,   50,    0,
    0,   50,   42,   49,   49,    0,   49,    0,    0,    0,
    0,   47,    0,    0,    0,   45,   50,   50,    0,   50,
    0,   75,   70,   68,   48,   69,    0,   71,    0,   46,
   76,   70,   68,    0,   69,    0,   71,   49,    0,    0,
   67,   31,   66,   47,   51,    0,    0,   51,    0,   67,
   50,   66,    0,   80,   70,   68,   48,   69,   52,   71,
    0,   52,   51,    0,    0,    0,    0,    0,    0,   49,
    0,    0,   67,    0,   66,    0,   52,    0,    0,    0,
   70,   68,   50,   69,    0,   71,    0,   31,   70,   68,
   32,   69,   27,   71,    0,    0,   51,    0,   67,    0,
   66,   28,    0,    0,    0,   22,   67,    0,   66,    0,
   52,    0,   36,   44,   45,    0,   46,   44,   45,   36,
   36,   36,   36,   36,   36,   41,    0,    0,   51,    0,
    0,   93,   41,   41,   41,   41,   41,   41,   42,   96,
    0,    0,   52,    0,    0,   42,   42,   42,   42,   42,
   42,   45,    0,    0,    0,    0,    0,    0,   45,   45,
   45,   45,   45,   45,    0,   46,    0,    0,    0,    0,
    0,    0,   46,   46,   46,   46,   46,   46,    0,   47,
    0,    0,    0,    0,    0,    0,   47,   47,   47,   47,
   47,   47,   48,    0,    0,    0,    0,    0,    0,   48,
   48,   48,   48,   48,   48,   49,    0,    0,    0,    0,
    0,    0,   49,   49,   49,   49,   49,   49,   50,   70,
   68,   97,   69,    0,   71,   50,   50,   50,   50,   50,
   50,    0,    0,    0,    0,    0,    0,   67,    0,   66,
    0,   25,    0,    0,   26,   27,   28,   29,   60,   61,
   62,   63,   64,   65,    0,    0,   30,   60,   61,   62,
   63,   64,   65,    0,   51,    0,    0,    0,   70,   68,
    0,   69,    0,   71,    0,   51,   51,    0,   52,    0,
   60,   61,   62,   63,   64,   65,   67,    0,   66,   52,
   52,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   60,   61,   62,   63,
   64,   65,   49,    0,   60,   61,   62,   63,   64,   65,
   70,   68,    0,   69,    0,   71,   55,   56,    0,    0,
    0,   59,    0,    0,    0,   72,   73,    0,   67,    0,
   66,   77,   78,    0,   81,   82,   83,   84,   85,   86,
   87,   88,   89,   90,   91,   92,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  102,    0,    0,  103,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   60,   61,   62,   63,   64,
   65,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   60,   61,   62,   63,   64,   65,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   60,   61,   62,   63,
};
static const short yycheck[] = {                         40,
   59,   40,   40,   40,   61,   59,   42,  274,   59,   11,
   59,   47,   41,   42,   43,   44,   45,   19,   47,   59,
   59,   76,  257,  258,  275,   41,   93,   43,   44,   45,
   59,   60,  274,   62,   91,   41,   44,   59,   41,   94,
   43,   44,   45,   59,   60,  123,   62,   40,   40,  104,
  274,   41,   91,   91,   44,  125,   59,   60,  260,   62,
   59,   41,  261,   61,   93,   41,  125,    0,   44,   59,
   60,  125,   62,    0,  125,   41,  125,   93,   41,   41,
  125,  125,   44,   59,   60,  125,   62,    6,   42,   43,
   93,   45,   41,   47,   41,   44,  125,   59,   60,   41,
   62,   18,   24,   93,   19,   41,   54,  102,   44,  125,
   59,   60,   -1,   62,   -1,   -1,   -1,   93,   41,   -1,
   -1,   44,  125,   59,   60,   -1,   62,   -1,   -1,   -1,
   -1,   93,   -1,   -1,   -1,  125,   59,   60,   -1,   62,
   -1,   41,   42,   43,   93,   45,   -1,   47,   -1,  125,
   41,   42,   43,   -1,   45,   -1,   47,   93,   -1,   -1,
   60,   59,   62,  125,   41,   -1,   -1,   44,   -1,   60,
   93,   62,   -1,   41,   42,   43,  125,   45,   41,   47,
   -1,   44,   59,   -1,   -1,   -1,   -1,   -1,   -1,  125,
   -1,   -1,   60,   -1,   62,   -1,   59,   -1,   -1,   -1,
   42,   43,  125,   45,   -1,   47,   -1,  261,   42,   43,
  261,   45,  261,   47,   -1,   -1,   93,   -1,   60,   -1,
   62,  261,   -1,   -1,   -1,  123,   60,   -1,   62,   -1,
   93,   -1,  261,  274,  275,   -1,  277,  274,  275,  268,
  269,  270,  271,  272,  273,  261,   -1,   -1,  125,   -1,
   -1,   93,  268,  269,  270,  271,  272,  273,  261,   93,
   -1,   -1,  125,   -1,   -1,  268,  269,  270,  271,  272,
  273,  261,   -1,   -1,   -1,   -1,   -1,   -1,  268,  269,
  270,  271,  272,  273,   -1,  261,   -1,   -1,   -1,   -1,
   -1,   -1,  268,  269,  270,  271,  272,  273,   -1,  261,
   -1,   -1,   -1,   -1,   -1,   -1,  268,  269,  270,  271,
  272,  273,  261,   -1,   -1,   -1,   -1,   -1,   -1,  268,
  269,  270,  271,  272,  273,  261,   -1,   -1,   -1,   -1,
   -1,   -1,  268,  269,  270,  271,  272,  273,  261,   42,
   43,   44,   45,   -1,   47,  268,  269,  270,  271,  272,
  273,   -1,   -1,   -1,   -1,   -1,   -1,   60,   -1,   62,
   -1,  259,   -1,   -1,  262,  263,  264,  265,  268,  269,
  270,  271,  272,  273,   -1,   -1,  274,  268,  269,  270,
  271,  272,  273,   -1,  261,   -1,   -1,   -1,   42,   43,
   -1,   45,   -1,   47,   -1,  272,  273,   -1,  261,   -1,
  268,  269,  270,  271,  272,  273,   60,   -1,   62,  272,
  273,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  268,  269,  270,  271,
  272,  273,   28,   -1,  268,  269,  270,  271,  272,  273,
   42,   43,   -1,   45,   -1,   47,   42,   43,   -1,   -1,
   -1,   47,   -1,   -1,   -1,   51,   52,   -1,   60,   -1,
   62,   57,   58,   -1,   60,   61,   62,   63,   64,   65,
   66,   67,   68,   69,   70,   71,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   97,   -1,   -1,  100,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  268,  269,  270,  271,  272,
  273,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  268,  269,  270,  271,  272,  273,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  268,  269,  270,  271,
};
#define YYFINAL 3
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 278
#if YYDEBUG
static const char *yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"'!'",0,0,0,0,0,0,"'('","')'","'*'","'+'","','","'-'",0,"'/'",0,0,0,0,0,0,0,0,0,
0,0,"';'","'<'","'='","'>'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,"'['",0,"']'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"'{'",0,"'}'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"KW_INT","KW_BYTE","KW_IF","KW_THEN",
"KW_ELSE","KW_WHILE","KW_PRINT","KW_RETURN","KW_READ","KW_TRUE","KW_FALSE",
"OPERATOR_LE","OPERATOR_GE","OPERATOR_EQ","OPERATOR_NE","OPERATOR_AND",
"OPERATOR_OR","TK_IDENTIFIER","LIT_INTEGER","LIT_CHAR","LIT_STRING",
"TOKEN_ERROR",
};
static const char *yyrule[] = {
"$accept : program",
"program : declarationList",
"program :",
"declarationList : declaration declarationList",
"declarationList : declaration",
"tipo : KW_INT",
"tipo : KW_BYTE",
"declaration : tipo TK_IDENTIFIER '[' LIT_INTEGER ']' ';'",
"declaration : tipo TK_IDENTIFIER ';'",
"declaration : tipo TK_IDENTIFIER '(' funcVarBlock ')' commandBlock",
"funcVarBlock : funcVar funcVarBlockCont",
"funcVarBlock :",
"funcVarBlockCont : ',' funcVar funcVarBlockCont",
"funcVarBlockCont :",
"funcVar : tipo TK_IDENTIFIER",
"commandBlock : '{' commands '}'",
"commands : command ';' commands",
"commands : command",
"commands :",
"command : assignment",
"command : read",
"command : print",
"command : return",
"command : if",
"command : while",
"command : commandBlock",
"command : ';'",
"assignment : TK_IDENTIFIER '=' exp",
"assignment : TK_IDENTIFIER '[' exp ']' '=' exp",
"read : KW_READ TK_IDENTIFIER",
"print : KW_PRINT LIT_STRING",
"print : KW_PRINT exp",
"return : KW_RETURN exp",
"if : KW_IF '(' exp ')' KW_THEN command KW_ELSE command",
"if : KW_IF '(' exp ')' KW_THEN command",
"while : KW_WHILE '(' exp ')' command",
"exp : TK_IDENTIFIER",
"exp : TK_IDENTIFIER '[' exp ']'",
"exp : TK_IDENTIFIER '(' args ')'",
"exp : LIT_INTEGER",
"exp : '(' exp ')'",
"exp : exp '+' exp",
"exp : exp '-' exp",
"exp : exp '*' exp",
"exp : exp '/' exp",
"exp : exp OPERATOR_LE exp",
"exp : exp OPERATOR_GE exp",
"exp : exp OPERATOR_EQ exp",
"exp : exp OPERATOR_NE exp",
"exp : exp '>' exp",
"exp : exp '<' exp",
"exp : exp OPERATOR_AND exp",
"exp : exp OPERATOR_OR exp",
"args : exp argsCont",
"args :",
"argsCont : ',' exp argsCont",
"argsCont :",

};
#endif
#if YYDEBUG
#include <stdio.h>
#endif

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH  500
#endif
#endif

#define YYINITSTACKSIZE 500

int      yydebug;
int      yynerrs;
int      yyerrflag;
int      yychar;
short   *yyssp;
YYSTYPE *yyvsp;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* variables for the parser stack */
static short   *yyss;
static short   *yysslim;
static YYSTYPE *yyvs;
static unsigned yystacksize;
#line 185 "parser.y"

int yyerror(char* error){
	printf("Error at line %d: %s\n",getLineNumber(),error);
	exit(3);
	
}
#line 394 "y.tab.c"
/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(void)
{
    int i;
    unsigned newsize;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = yystacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = yyssp - yyss;
    newss = (yyss != 0)
          ? (short *)realloc(yyss, newsize * sizeof(*newss))
          : (short *)malloc(newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    yyss  = newss;
    yyssp = newss + i;
    newvs = (yyvs != 0)
          ? (YYSTYPE *)realloc(yyvs, newsize * sizeof(*newvs))
          : (YYSTYPE *)malloc(newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    yyvs = newvs;
    yyvsp = newvs + i;
    yystacksize = newsize;
    yysslim = yyss + newsize - 1;
    return 0;
}

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

    if (yyss == NULL && yygrowstack()) goto yyoverflow;
    yyssp = yyss;
    yyvsp = yyvs;
    yystate = 0;
    *yyssp = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yysslim && yygrowstack())
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yyssp = yytable[yyn];
        *++yyvsp = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yysslim && yygrowstack())
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yyssp = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yyvsp[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 73 "parser.y"
	{ yyval.ast = yyvsp[0].ast; forEachDo(yyval.ast, astPrintSingle); astCreateCode(yyval.ast); }
break;
case 2:
#line 74 "parser.y"
	{ yyval.ast = 0; }
break;
case 3:
#line 78 "parser.y"
	{ yyval.ast = astCreate(AST_DECL,0,yyvsp[-1].ast,yyvsp[0].ast,0,0); }
break;
case 4:
#line 79 "parser.y"
	{ yyval.ast = astCreate(AST_DECL,0,yyvsp[0].ast,0,0,0); }
break;
case 5:
#line 83 "parser.y"
	{ yyval.ast = astCreate(AST_INT,0,0,0,0,0);}
break;
case 6:
#line 84 "parser.y"
	{ yyval.ast = astCreate(AST_BYTE,0,0,0,0,0);}
break;
case 7:
#line 88 "parser.y"
	{ yyval.ast = astCreate(AST_VECTDEC,yyvsp[-4].symbol,yyvsp[-5].ast,astCreate(AST_REF,yyvsp[-2].symbol,0,0,0,0),0,0);}
break;
case 8:
#line 89 "parser.y"
	{ yyval.ast = astCreate(AST_VARDEC,yyvsp[-1].symbol,yyvsp[-2].ast,0,0,0); }
break;
case 9:
#line 90 "parser.y"
	{ yyval.ast = astCreate(AST_FUNDEC,yyvsp[-4].symbol,yyvsp[-5].ast,yyvsp[-2].ast,yyvsp[0].ast,0); }
break;
case 10:
#line 94 "parser.y"
	{ yyval.ast = astCreate(AST_FUNCVAR,0,yyvsp[-1].ast,yyvsp[0].ast,0,0); }
break;
case 11:
#line 95 "parser.y"
	{ yyval.ast = 0; }
break;
case 12:
#line 98 "parser.y"
	{ yyval.ast = astCreate(AST_FUNCVAR,0,yyvsp[-1].ast,yyvsp[0].ast,0,0); }
break;
case 13:
#line 99 "parser.y"
	{ yyval.ast = 0; }
break;
case 14:
#line 102 "parser.y"
	{ yyval.ast = astCreate(AST_DECS,yyvsp[0].symbol,yyvsp[-1].ast,0,0,0); }
break;
case 15:
#line 106 "parser.y"
	{ yyval.ast = astCreate(AST_COMBLK,0,yyvsp[-1].ast,0,0,0); }
break;
case 16:
#line 110 "parser.y"
	{ yyval.ast = astCreate(AST_COMMANDS,0,yyvsp[-2].ast,yyvsp[0].ast,0,0); }
break;
case 17:
#line 111 "parser.y"
	{ yyval.ast = yyvsp[0].ast; }
break;
case 18:
#line 112 "parser.y"
	{ yyval.ast = 0;  }
break;
case 19:
#line 116 "parser.y"
	{ yyval.ast = yyvsp[0].ast; }
break;
case 20:
#line 117 "parser.y"
	{ yyval.ast = yyvsp[0].ast; }
break;
case 21:
#line 118 "parser.y"
	{ yyval.ast = yyvsp[0].ast; }
break;
case 22:
#line 119 "parser.y"
	{ yyval.ast = yyvsp[0].ast; }
break;
case 23:
#line 120 "parser.y"
	{ yyval.ast = yyvsp[0].ast; }
break;
case 24:
#line 121 "parser.y"
	{ yyval.ast = yyvsp[0].ast; }
break;
case 25:
#line 122 "parser.y"
	{ yyval.ast = yyvsp[0].ast; }
break;
case 26:
#line 123 "parser.y"
	{ yyval.ast = astCreate(AST_EPTCMD,0,0,0,0,0); }
break;
case 27:
#line 127 "parser.y"
	{ yyval.ast = astCreate(AST_ASSIGN,yyvsp[-2].symbol,yyvsp[0].ast,0,0,0); }
break;
case 28:
#line 128 "parser.y"
	{ yyval.ast = astCreate(AST_ASSIGN,yyvsp[-5].symbol,yyvsp[-3].ast,yyvsp[0].ast,0,0); }
break;
case 29:
#line 133 "parser.y"
	{ yyval.ast = astCreate(AST_READ,yyvsp[0].symbol,0,0,0,0); }
break;
case 30:
#line 137 "parser.y"
	{ yyval.ast = astCreate(AST_PRINT,yyvsp[0].symbol,0,0,0,0); }
break;
case 31:
#line 138 "parser.y"
	{ yyval.ast = astCreate(AST_PRINT,0,yyvsp[0].ast,0,0,0); }
break;
case 32:
#line 142 "parser.y"
	{ yyval.ast = astCreate(AST_RETURN,0,yyvsp[0].ast,0,0,0); }
break;
case 33:
#line 146 "parser.y"
	{ yyval.ast = astCreate(AST_IFELSE,0,yyvsp[-5].ast,yyvsp[-2].ast,yyvsp[0].ast,0); }
break;
case 34:
#line 147 "parser.y"
	{ yyval.ast = astCreate(AST_IF,0,yyvsp[-3].ast,yyvsp[0].ast,0,0); }
break;
case 35:
#line 151 "parser.y"
	{ yyval.ast = astCreate(AST_WHILE,0,yyvsp[-2].ast,yyvsp[0].ast,0,0); }
break;
case 36:
#line 155 "parser.y"
	{ yyval.ast = astCreate(AST_REF,yyvsp[0].symbol,0,0,0,0); }
break;
case 37:
#line 156 "parser.y"
	{ yyval.ast = astCreate(AST_VEC,hashMakeTemp(),astCreate(AST_VEC_USE,yyvsp[-3].symbol,yyvsp[-1].ast,0,0,0),0,0,0);}
break;
case 38:
#line 157 "parser.y"
	{ yyval.ast = astCreate(AST_FUNC_CALL,hashMakeTemp(),astCreate(AST_FUNC_USE,yyvsp[-3].symbol,yyvsp[-1].ast,0,0,0),0,0,0);}
break;
case 39:
#line 158 "parser.y"
	{ yyval.ast = astCreate(AST_REF,yyvsp[0].symbol,0,0,0,0); }
break;
case 40:
#line 159 "parser.y"
	{ yyval.ast = yyvsp[-1].ast; }
break;
case 41:
#line 160 "parser.y"
	{ yyval.ast = astCreate(AST_ADD,hashMakeTemp(),yyvsp[-2].ast,yyvsp[0].ast,0,0); }
break;
case 42:
#line 161 "parser.y"
	{ yyval.ast = astCreate(AST_SUB,hashMakeTemp(),yyvsp[-2].ast,yyvsp[0].ast,0,0); }
break;
case 43:
#line 162 "parser.y"
	{ yyval.ast = astCreate(AST_MUL,hashMakeTemp(),yyvsp[-2].ast,yyvsp[0].ast,0,0); }
break;
case 44:
#line 163 "parser.y"
	{ yyval.ast = astCreate(AST_DIV,hashMakeTemp(),yyvsp[-2].ast,yyvsp[0].ast,0,0); }
break;
case 45:
#line 164 "parser.y"
	{ yyval.ast = astCreate(AST_LE ,hashMakeTemp(),yyvsp[-2].ast,yyvsp[0].ast,0,0); }
break;
case 46:
#line 165 "parser.y"
	{ yyval.ast = astCreate(AST_GE ,hashMakeTemp(),yyvsp[-2].ast,yyvsp[0].ast,0,0); }
break;
case 47:
#line 166 "parser.y"
	{ yyval.ast = astCreate(AST_EQ ,hashMakeTemp(),yyvsp[-2].ast,yyvsp[0].ast,0,0); }
break;
case 48:
#line 167 "parser.y"
	{ yyval.ast = astCreate(AST_NE ,hashMakeTemp(),yyvsp[-2].ast,yyvsp[0].ast,0,0); }
break;
case 49:
#line 168 "parser.y"
	{ yyval.ast = astCreate(AST_BT ,hashMakeTemp(),yyvsp[-2].ast,yyvsp[0].ast,0,0); }
break;
case 50:
#line 169 "parser.y"
	{ yyval.ast = astCreate(AST_ST ,hashMakeTemp(),yyvsp[-2].ast,yyvsp[0].ast,0,0); }
break;
case 51:
#line 170 "parser.y"
	{ yyval.ast = astCreate(AST_AND,hashMakeTemp(),yyvsp[-2].ast,yyvsp[0].ast,0,0); }
break;
case 52:
#line 171 "parser.y"
	{ yyval.ast = astCreate(AST_OR ,hashMakeTemp(),yyvsp[-2].ast,yyvsp[0].ast,0,0); }
break;
case 53:
#line 175 "parser.y"
	{ yyval.ast = astCreate(AST_ARGS,0,yyvsp[-1].ast,yyvsp[0].ast,0,0); }
break;
case 54:
#line 176 "parser.y"
	{ yyval.ast = 0; }
break;
case 55:
#line 180 "parser.y"
	{ yyval.ast = astCreate(AST_ARGS,0,yyvsp[-1].ast,yyvsp[0].ast,0,0); }
break;
case 56:
#line 181 "parser.y"
	{ yyval.ast = 0; }
break;
#line 803 "y.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yysslim && yygrowstack())
    {
        goto yyoverflow;
    }
    *++yyssp = (short) yystate;
    *++yyvsp = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    return (1);

yyaccept:
    return (0);
}
