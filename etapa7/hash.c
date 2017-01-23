#include "hash.h"


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
	    newNode->dataType = DT_UNKNOWN;
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
	sprintf(hashBuffer,".TempValue%d",nextTemp++);
	return hashInsert(hashBuffer,REF_VARIABLE);

}

hashNode* makeLabel(){
    sprintf(hashBuffer,".TempLabel%d",nextTemp++);
	return hashInsert(hashBuffer,REF_LABEL);
}

hashNode* hashPrintAssembly(FILE* assembly){
	int i;
	hashNode* iterator;
	
	
	
	for (i=0;i<HASH_SIZE+1; i++){
		iterator = hashTable[i];
		
		while(iterator){
		    if(iterator->type == SYMBOL_LIT_STRING){
		        fprintf(assembly,"%s:\n\t.string \"%s\"\n",iterator->text,iterator->text);
		    }
		    else if(iterator->type == SYMBOL_LIT_INTEGER){
		        fprintf(assembly,".globl .%s\n"
		                         "\t.data\n"
		                         "\t.align 4\n"
		                         "\t.type .%s,@object\n"
		                         "\t.size .%s, 4\n"
		                         ".%s:\n"
		                         "\t .long %s\n",
		                         iterator->text,
		                         iterator->text,
		                         iterator->text,
		                         iterator->text,
		                         iterator->text);
		    }else
			if(iterator->type == REF_VARIABLE){
				switch(iterator->dataType){
					
					case DT_BYTE:{ fprintf(assembly,".globl .%s\n"
		                         "\t.data\n"
		                         "\t.align 1\n"
		                         "\t.type .%s,@object\n"
		                         "\t.size .%s, 1\n"
		                         ".%s:\n"
		                         "\t .byte 0\n",
		                         iterator->text,
		                         iterator->text,
		                         iterator->text,
		                         iterator->text);break;
		                         } 
					case DT_BOOLEAN: {fprintf(assembly,".globl .%s\n"
		                         "\t.data\n"
		                         "\t.align 1\n"
		                         "\t.type .%s,@object\n"
		                         "\t.size .%s, 1\n"
		                         ".%s:\n"
		                         "\t .byte 0\n",
		                         iterator->text,
		                         iterator->text,
		                         iterator->text,
		                         iterator->text);break;
		                         }
		           default: {fprintf(assembly,".globl .%s\n"
		                         "\t.data\n"
		                         "\t.align 4\n"
		                         "\t.type .%s,@object\n"
		                         "\t.size .%s, 4\n"
		                         ".%s:\n"
		                         "\t .long 0\n",
		                         iterator->text,
		                         iterator->text,
		                         iterator->text,
		                         iterator->text);break;
		                         }              
				}
			}
			else if(iterator->type == REF_VECTOR){
				switch(iterator->dataType){
					case DT_INT: fprintf(assembly,".comm .%s,%d,%d\n",iterator->text,4*iterator->vectorSize,4);break;
					case DT_BYTE: fprintf(assembly,".comm .%s,%d,%d\n",iterator->text,iterator->vectorSize,1); break;
				}
			}
			iterator = iterator->next;
		}
	}
	//preparing for %d strings
	fprintf(assembly,".LC0: \n\t.string \"%%d\"\n\t.text\n");
}

