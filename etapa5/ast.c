#include "ast.h"

ast* astCreate(int type,int line, hashNode* symbol,ast* s0,ast* s1,ast* s2,ast* s3){
	ast* newAstNode = calloc(1,sizeof(ast));
	newAstNode->dataType = DT_UNKNOWN;
	newAstNode->type = type;
	newAstNode->line = line;
	newAstNode->symbol = symbol;
	newAstNode->son[0] = s0;
	newAstNode->son[1] = s1;
	newAstNode->son[2] = s2;
	newAstNode->son[3] = s3;
	
	return newAstNode;
	
}


////========//========//========//========//========//=========

void astPrintSingle(ast* node){
	int i;
	if(node){
		printf("(Type: ");
		switch(node->type){
		    case AST_REF:		{ printf(" AST_REF"); break;}
			case AST_ADD:		{ printf(" AST_ADD"); break;}
			case AST_SUB:		{ printf(" AST_SUB"); break;}
			case AST_MUL: 		{ printf(" AST_MUL"); break;}
			case AST_DIV:		{ printf(" AST_DIV"); break;}
			case AST_AND: 		{ printf(" AST_AND"); break;}
			case AST_OR:		{ printf(" AST_OR"); break;}
			case AST_LE:		{ printf(" AST_LE"); break;}
			case AST_GE:		{ printf(" AST_GE"); break;}
			case AST_EQ:		{ printf(" AST_EQ"); break;}
			case AST_NE:		{ printf(" AST_NE"); break;}
			case AST_BT :		{ printf(" AST_BT"); break;}	
			case AST_ST :		{ printf(" AST_ST"); break;}
			case AST_ARGS:		{ printf(" AST_ARGS"); break;}
			case AST_FUNC_CALL:	{ printf(" AST_FUNC_CALL"); break;}
			case AST_WHILE:		{ printf(" AST_WHILE"); break;}
			case AST_IF:		{ printf(" AST_IF"); break;}
			case AST_IFELSE:	{ printf(" AST_IFELSE"); break;}
			case AST_RETURN:	{ printf(" AST_RETURN"); break;}
			case AST_PRINT:		{ printf(" AST_PRINT"); break;}
			case AST_READ:		{ printf(" AST_READ"); break;}        
			case AST_ASSIGN:	{ printf(" AST_ASSIGN"); break;}      
			case AST_EPTCMD:	{ printf(" AST_EPTCMD"); break;}      
			case AST_COMMANDS:	{ printf(" AST_COMMANDS"); break;}    
			case AST_COMBLK:	{ printf(" AST_COMBLK"); break;}      
			case AST_FUNCVAR:	{ printf(" AST_FUNCVAR"); break;}     
			case AST_FUNDEC:	{ printf(" AST_FUNDEC"); break;}      
			case AST_VARDEC:	{ printf(" AST_VARDEC"); break;}
			case AST_VECTDEC:   { printf(" AST_VECTDEC"); break;}      
			case AST_DECS:		{ printf(" AST_DECS"); break;}
			case AST_INT:		{ printf(" AST_INT"); break;} 
			case AST_BYTE:		{ printf(" AST_BYTE"); break;} 
			case AST_DECL:		{ printf(" AST_DECL"); break;}
            case AST_VEC:       { printf(" AST_VEC"); break;}      
		    case AST_FUNC_USE:  { printf(" AST_FUNC_USE"); break;} 

			default: 		    { printf(" UnknownType"); break;}
		}
		printf(", Hash: %s",node->symbol ? node->symbol->text : "NULL");
		
		printf(")\n");		
	}

}

//========//========//========//========//========//=========

void forEachDo(ast* astree, void (*fun) (ast* ast)){
	int i;
	if (astree){
		fun (astree);
		for (i=0; i<AST_MAX_SONS; i++){
			forEachDo(astree->son[i],fun);
		}
	}
}

//========//========//========//========//========//=========

void astCreateCode(ast* node){
    if(node){		
		switch(node->type){
			case AST_ADD:		{ astPrintBinOp(node,"+"); break;}
			case AST_SUB:		{ astPrintBinOp(node,"-"); break;}
			case AST_MUL: 		{ astPrintBinOp(node,"*"); break;}
			case AST_DIV:		{ astPrintBinOp(node,"/"); break;}
			case AST_AND: 		{ astPrintBinOp(node,"&&"); break;}
			case AST_OR:		{ astPrintBinOp(node,"||"); break;}
			case AST_LE:		{ astPrintBinOp(node,"<="); break;}
			case AST_GE:		{ astPrintBinOp(node,">="); break;}
			case AST_EQ:		{ astPrintBinOp(node,"=="); break;}
			case AST_NE:		{ astPrintBinOp(node,"!="); break;}
			case AST_BT :		{ astPrintBinOp(node,">"); break;}	
			case AST_ST :		{ astPrintBinOp(node,"<"); break;}
			case AST_ARGS:		{ astPrintArgs(node); break;}
			case AST_FUNC_CALL:	{ astPrintFunCall(node); break;}
			case AST_WHILE:		{ astPrintWhile(node); break;}
			case AST_IF:		{ astPrintIf(node); break;}
			case AST_IFELSE:	{ astPrintIfElse(node); break;}
			case AST_RETURN:	{ astPrintReturn(node); break;}
			case AST_PRINT:		{ astPrintPrint(node); break;}
			case AST_READ:		{ astPrintRead(node); break;}        
			case AST_ASSIGN:	{ astPrintAss(node); break;}      
			case AST_EPTCMD:	{ astPrintEmptyCmd(node); break;}      
			case AST_COMMANDS:	{ astPrintcommands(node); break;}    
			case AST_COMBLK:	{ astPrintCmdBlk(node); break;}      
			case AST_FUNCVAR:	{ astPrintFuncVars(node); break;}     
			case AST_FUNDEC:	{ astPrintFuncDec(node); break;}      
			case AST_VARDEC:	{ astPrintVarDec(node); break;}
			case AST_VECTDEC:   { astPrintVectDec(node); break;}      
			case AST_DECS:		{ astPrintDecs(node); break;}
			case AST_DECL:		{ astPrintDecl(node);break;}
            case AST_VEC_USE:        { astPrintVec(node); break;}      
			case AST_REF:   		{ astPrintRef(node);break;}
                                   
		}
	}
}

//========//========//========//========//========//=========

void astPrintRef(ast* node){
	fprintf(outputFile,"%s",node->symbol->text); 
} 

//========//========//========//========//========//=========

void astPrintBinOp(ast* node, char* opSymbol){ 
     astCreateCode(node->son[0]);  
     fprintf(outputFile," %s ",opSymbol);
     astCreateCode(node->son[1]);
    
}
 
//========//========//========//========//========//=========

void astPrintArgs(ast* node){ 
	astCreateCode(node->son[0]);
	if (node->son[1])
	{
	      fprintf(outputFile, ", ");
      	astCreateCode(node->son[1]);
      }
}
 
//========//========//========//========//========//=========
/*   |TK_IDENTIFIER '(' args ')'     { $$ = astCreate(AST_FUNC_CALL,hashMakeTemp(),astCreate(AST_FUNC_USE,$1,$3,0,0,0),0,0,0);}*/
void astPrintFunCall(ast* node){
	
    fprintf(outputFile,"%s ( ",node->symbol->text);
    astCreateCode(node->son[0]);
    fprintf(outputFile," )");
}

void astPrintFunUse(ast*node){

	astCreateCode(node->son[0]->son[0]);
	/*astCreateCode(node->son[0]->son[1]);*/
}
 
//========//========//========//========//========//=========

void astPrintWhile(ast* node){ 
    fprintf(outputFile,"while ( ");
    astCreateCode(node->son[0]);
    fprintf(outputFile,")");
    astCreateCode(node->son[1]);
}
 
//========//========//========//========//========//=========

void astPrintIf(ast* node){ 
     
     fprintf(outputFile,"if ( ");
     astCreateCode(node->son[0]);
     fprintf(outputFile,") then \n");
     astCreateCode(node->son[1]);   
}
 
//========//========//========//========//========//=========

void astPrintIfElse(ast* node){ 
    fprintf(outputFile,"if ( ");
    astCreateCode(node->son[0]);
    fprintf(outputFile,") then \n");
    astCreateCode(node->son[1]);
    fprintf(outputFile,"\nelse ");
    astCreateCode(node->son[2]);
}
 
//========//========//========//========//========//=========

void astPrintReturn(ast* node){ 
    
    fprintf(outputFile,"return ");
    astCreateCode(node->son[0]);
}
 
//========//========//========//========//========//=========

void astPrintPrint(ast* node){
   
    fprintf(outputFile,"print ");
    astCreateCode(node->son[0]);
   
}
 
//========//========//========//========//========//=========

void astPrintRead(ast* node){ 
    fprintf(outputFile,"read %s",node->symbol->text);
}
         
//========//========//========//========//========//=========

void astPrintAss(ast* node){ 
    
    fprintf(outputFile,"%s = ",node->symbol->text);
    astCreateCode(node->son[0]);
    
}
       
//========//========//========//========//========//=========

void astPrintEmptyCmd(ast* node){ 
    fprintf(outputFile,";\n");
}
       
//========//========//========//========//========//=========

void astPrintcommands(ast* node){ 
    astCreateCode(node->son[0]);
    if (node->son[1]){
        fprintf(outputFile,";\n");
        astCreateCode(node->son[1]);
    }
}
     
//========//========//========//========//========//=========

void astPrintCmdBlk(ast* node){ 
    fprintf(outputFile,"{\n");
    astCreateCode(node->son[0]);
    fprintf(outputFile,"}\n");
}
       
//========//========//========//========//========//=========


void astPrintVarDec(ast* node){ 
    switch(node->son[0]->type){
        case AST_INT:	 {  fprintf(outputFile,"int %s;\n",node->symbol->text);  break;  }             
        case AST_BYTE:   {  fprintf(outputFile,"byte %s;\n",node->symbol->text);  break;  }
    }
}
 
//========//========//========//========//========//=========

void astPrintVectDec(ast* node){ 
    switch(node->son[0]->type){
        case AST_INT:{  
                fprintf(outputFile,"int %s [ %s ];\n",node->symbol->text,node->son[1]->symbol->text);                             
                break; 
                }                                    
        case AST_BYTE:   {  
                fprintf(outputFile,"byte %s [ %s ];\n",node->symbol->text,node->son[1]->symbol->text); 
                break;
                }
    }
}

       
//========//========//========//========//========//=========

void astPrintFuncVars(ast* node){
	astCreateCode(node->son[0]);
	if(node->son[1]){
		fprintf(outputFile,", ");
		astCreateCode(node->son[1]);
	}
}
      
//========//========//========//========//========//=========
    
void astPrintFuncDec(ast* node){ 
	switch(node->son[0]->type){
		case AST_INT:	{fprintf(outputFile,"int ");break;}	
		case AST_BYTE:	{fprintf(outputFile,"byte ");break;}
	}
	fprintf(outputFile,"%s ( ",node->symbol->text);
	astCreateCode(node->son[1]);
	fprintf(outputFile," )");
	astCreateCode(node->son[2]);	
}
       
//========//========//========//========//========//=========

void astPrintDecs(ast* node){ 
	switch(node->son[0]->type){
		case AST_INT:	{fprintf(outputFile,"int ");break;}	
		case AST_BYTE:	{fprintf(outputFile,"byte ");break;}
	}
	fprintf(outputFile,"%s",node->symbol->text);
}


//========//========//========//========//========//=========


void astPrintVec(ast* node){
    fprintf(outputFile,"%s [ ",node->symbol->text);
    astCreateCode( node->son[0]);
    fprintf(outputFile," ]");
}

void astPrintDecl(ast* node){
	astCreateCode(node->son[0]);
	astCreateCode(node->son[1]);
}

 
