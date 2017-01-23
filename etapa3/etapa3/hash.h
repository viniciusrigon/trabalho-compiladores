#ifndef	HASH_HEADER
#define HASH_HEADER

#define HASH_SIZE 997
#define SYMBOL_UNDEFINED 0
#define SYMBOL_LIT_INTEGER 1
#define SYMBOL_LIT_TRUE 3
#define SYMBOL_LIT_FALSE 4
#define SYMBOL_LIT_CHAR 5
#define SYMBOL_LIT_STRING 6
#define SYMBOL_IDENTIFIER 7

#define SYMBOL_VARIABLE 8


typedef struct node{
	char* 			text;
	int 			type;
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

#endif
