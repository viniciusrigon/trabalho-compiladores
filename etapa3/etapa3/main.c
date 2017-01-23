#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern FILE* yyin;
extern int running;
FILE* outputFile;

int main(int argc, char** argv)
{
    if (argc!=3){
        printf("Call this program with the name of 2 files!");
        return 1;
    }
    if (!(yyin = fopen(argv[1],"r"))){
        printf("%s is not a valid file\n",argv[1]);
        return 1;
    }
    if(!(outputFile = fopen(argv[2],"w"))){
        printf("%s is not a valid file\n",argv[2]);
        fclose(yyin);
        return 1;
    }
    
	initMe();
	yyparse();	
    
    fclose(yyin);
    fclose(outputFile);
	return 0;
}
