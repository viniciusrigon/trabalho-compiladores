%{
#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "ast.h"
#include "y.tab.h"
int running;
int lineNumber;

void clearQuoutes();


%}


LIT_NUM [0-9]
LIT_ALFANUM [_A-Za-z0-9]
LIT_ALFAB   [_A-Za-z]
LIT_SPEC [-,;:(){}+*/<>=!]|"["|"]"



%x MULT_COMMENT
%x SIMPLE_COMMENT 


%%	
"int"								{ return KW_INT;	}
"byte"								{ return KW_BYTE;	}
"if"								{ return KW_IF;		}
"then"								{ return KW_THEN;	}
"else"								{ return KW_ELSE;	}
"while"								{ return KW_WHILE;	}
"print"								{ return KW_PRINT;	}
"return"							{ return KW_RETURN;	}
"read"								{ return KW_READ;	}
"true"                              { yylval.symbol = hashInsert (yytext,SYMBOL_LIT_TRUE); return KW_TRUE;   }
"false"                             { yylval.symbol = hashInsert (yytext,SYMBOL_LIT_FALSE); return KW_FALSE;   }

"<="								{ return OPERATOR_LE;	}
">="								{ return OPERATOR_GE;	}
"=="								{ return OPERATOR_EQ;	}
"!="								{ return OPERATOR_NE;	}
"&&"								{ return OPERATOR_AND;	}
"||"								{ return OPERATOR_OR;	}
" "|"	"                           				{   }


"/*"			BEGIN(MULT_COMMENT);
"//"            BEGIN(SIMPLE_COMMENT);

{LIT_NUM}+ 				{ yylval.symbol = hashInsert(yytext,SYMBOL_LIT_INTEGER); return  LIT_INTEGER; }
{LIT_SPEC}				{ return yytext[0]; }
{LIT_ALFAB}{LIT_ALFANUM}*		{ yylval.symbol = hashInsert(yytext,SYMBOL_IDENTIFIER); return TK_IDENTIFIER;} 
\"(\\.|[^\\"])*\" 	{clearQuoutes(); yylval.symbol = hashInsert(yytext,SYMBOL_LIT_STRING); return LIT_STRING;}
("'"(.|\\n|\\t|\\v|\\b|\\r|\\f|\\a|\\0)"'")  	{clearQuoutes(); yylval.symbol = hashInsert(yytext, SYMBOL_LIT_CHAR); return LIT_CHAR;}

.						{ return TOKEN_ERROR;	}
\n						{ ++lineNumber;	}

<MULT_COMMENT>"*/"				BEGIN(INITIAL);
<MULT_COMMENT>.					{	}
<MULT_COMMENT>"\n"				{ ++lineNumber; }

<SIMPLE_COMMENT>"\n"				{ ++lineNumber; BEGIN(INITIAL); }
<SIMPLE_COMMENT>.				{   }

%%

int getLineNumber()
{
	return lineNumber;
}

void initMe(){
	running=1;
	lineNumber=1;
	hashInit();
}

void clearQuoutes(){
    int i;
    for (i=1; i<strlen(yytext); i++){
        yytext[i-1]=yytext[i];
    }
    /* remove last quote */
    yytext[i-2]=yytext[i]; 
}

int yywrap()
{
	running=0;
	hashPrint();
	printf("The file has %d lines.\n", lineNumber-1);
	return 1;
}
