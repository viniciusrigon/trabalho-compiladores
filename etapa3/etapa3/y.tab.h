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
typedef union {
    hashNode* symbol;
    ast*    ast;
    } YYSTYPE;
extern YYSTYPE yylval;
