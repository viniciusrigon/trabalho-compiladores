#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*it initializes the hash table*/
void hashInit(){
	int i;
	for (i=0; i<HASH_SIZE+1;i++){
		hashTable[i]=NULL;	
	}
	nextTemp=0;
}

/*It calculates the hash address of the token*/
int hashAddress(char* text){
	int i;
	int address=1;
	for (i=0; i<strlen(text)-1;i++){
		address=((address*text[i]) % (HASH_SIZE))+1;
		
	}
	return address;
}

/*returns the node or "null" if the info is not in the hash table*/
hashNode* hashFind(char* text, int type){
	int infoAddress;
	hashNode* foundNode;
	hashNode* searchNode;
	infoAddress=hashAddress(text);
	foundNode=NULL;
	searchNode=NULL;
	for (searchNode=hashTable[infoAddress]; searchNode!=NULL; searchNode=searchNode->next){
		if (strcmp(searchNode->text,text)==0 && searchNode->type==type){
			foundNode=searchNode;
			break;	
		}
	}
	return foundNode;	
}


hashNode* hashInsert(char* text, int type){
	int infoAddress;
	hashNode* newNode;
	newNode=hashFind(text,type);
	if( newNode==NULL ){
	    infoAddress=hashAddress(text);
	    
	    newNode = calloc(1,sizeof(hashNode));	    
	    newNode->text = (char*)calloc(1,strlen(text)+1);
	    newNode->type = type;
	    
		if (newNode->text != NULL)
		    strcpy(newNode->text,text);	
	    
	    newNode->next=hashTable[infoAddress];
	    hashTable[infoAddress]=newNode;
	}
	return newNode;
	
}

void hashPrint()
{
	int i;
	hashNode* nodo;
	for (i = 0; i < HASH_SIZE + 1; ++i)
	{
		if (hashTable[i] == NULL)
			printf("");
		else{
			nodo = hashTable[i];
			printf("(");
			for(; nodo != NULL; nodo = nodo->next)
				printf("\n(%s,%d) ",nodo->text,nodo->type);
			printf(")");
			}
	}
	
	printf("\n");    
}

hashNode* hashMakeTemp(){
	sprintf(hashBuffer,"My_ReAlLy_StRaNgE_vAr_%d",nextTemp++);
	return hashInsert(hashBuffer,SYMBOL_VARIABLE);

}

