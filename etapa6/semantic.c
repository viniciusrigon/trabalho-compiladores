#include "semantic.h"


void fullSemanticAnalizis(ast* root){
    int redeclared;
    int notDeclared;
    int useError;
    int dataTypeError;
    
    //checks the ast for double declarations. (a)
    redeclared = typeVerification(root);
    //checks the ast for undeclared identifiers.(a) part 2
    notDeclared = undeclaredVerification(root);
    if (redeclared != NO_ERROR) fprintf(stdout,"Please, fix the 'redeclared' error(s) above and try to recompile your code.\n");
    if (notDeclared != NO_ERROR) fprintf(stdout,"Please, fix the 'not declared' error(s) above and try to recompile your code.\n");
    //if ((redeclared != NO_ERROR) || (notDeclared != NO_ERROR)) return;
        
        
    //checks the ast for identifiers not properly used. (b)
    useError = useVerification(root);
    if( useError != NO_ERROR) { 
        fprintf(stdout,"Please, fix the 'usage' error(s) above and try to recompile your code.\n"); 
        exit(1);
    }
    
    
    //checks and sets the types of the expressions . (c)
    dataTypeDecsVerification(root); // doesnt need verifications 'cause all decs are declared with a type.
    dataTypeError = dataTypeVerification(root);
    if( dataTypeError == DATATYPE_ERROR) { 
        fprintf(stdout,"Please, fix the 'type' error(s) above and try to recompile your code.\n"); 
        //return;
    }
    
    
    //checks the ast for the correct call of functions
    if (argumentsVerification(root) == ARGUMENT_ERROR){ 
        fprintf(stdout,"Please, fix the 'argument' error(s) above and try to recompile your code.\n"); 
        exit(1);
    }
}

//######################################################################################################
//######################################################################################################

int typeVerification(ast* node){
    int error=NO_ERROR;
    if (node){
        switch(node->type){
            case AST_DECL: { 
                        if (typeVerification(node->son[0]) != NO_ERROR ) error = REDECLARED;
                        if (typeVerification(node->son[1]) != NO_ERROR ) error = REDECLARED; 
                        break;
                    }
            case AST_FUNCVAR:{
                        if (typeVerification(node->son[0]) != NO_ERROR ) error = REDECLARED;
                        if (typeVerification(node->son[1]) != NO_ERROR ) error = REDECLARED;
                        break;
                    }
            case AST_VECTDEC: {
                        if (node->symbol->type == SYMBOL_IDENTIFIER){
                            node->symbol->type = REF_VECTOR;    
                        }
                        else{
                            fprintf(stdout,"Semantic Error(line %d): '%s' redeclared.\n",node->line,node->symbol->text);
                            error = REDECLARED;
                        }
                        break;
                    }
            case AST_VARDEC:{
                        if (node->symbol->type == SYMBOL_IDENTIFIER){
                            node->symbol->type = REF_VARIABLE;    
                        }
                        else{
                            fprintf(stdout,"Semantic Error(line %d): '%s' redeclared.\n",node->line,node->symbol->text);
                            error = REDECLARED;
                        }
                        break;
                    }
            case AST_FUNDEC:{
                        if (node->symbol->type == SYMBOL_IDENTIFIER){
                            node->symbol->type = REF_FUNCTION;
                            typeVerification(node->son[1]); //we have to verify the arguments of the function
                        }
                        else{
                            fprintf(stdout,"Semantic Error(line %d): '%s' redeclared.\n",node->line,node->symbol->text);
                            error = REDECLARED;
                        }
                        break;
                    }
            
            
            case AST_DECS:{
                        if (node->symbol->type == SYMBOL_IDENTIFIER){
                            node->symbol->type = REF_VARIABLE;
                        }
                        else{
                            fprintf(stdout,"Semantic Error(line %d): '%s' redeclared.\n",node->line,node->symbol->text);
                            error = REDECLARED;
                        }
                        break;
                    }
            default:{
                        fprintf(stdout,"Semantic Error(line %d): Can't define '%s' as variable, vector or function.\n",node->line,node->symbol->text);
                        error = UNKNOWN;
                        break;
                    }
        }//switch(node->type)
    }//if (node)
    return error;
}

//######################################################################################################
//######################################################################################################

int undeclaredVerification(ast* node){
    int error = NO_ERROR;
    if (node){
        switch(node->type){
            case AST_REF:{
                        if(node->symbol->type == SYMBOL_IDENTIFIER){
                            fprintf(stdout,"Semantic Error(line %d): '%s' was not declared.\n",node->line,node->symbol->text);
                            error = NOT_DECLARED;
                        }
                        break;
                    }
            case AST_VEC_USE:{
                        if(node->symbol->type == SYMBOL_IDENTIFIER){
                            fprintf(stdout,"Semantic Error(line %d): '%s' was not declared.\n",node->line,node->symbol->text);
                            error = NOT_DECLARED;
                        }
                        break;
                    }
            case AST_FUNC_CALL:{
                        if(node->symbol->type == SYMBOL_IDENTIFIER){
                            fprintf(stdout,"Semantic Error(line %d): '%s' was not declared.\n",node->line,node->symbol->text);
                            error = NOT_DECLARED;
                        }
                        break;
                    }
            case AST_READ:{
                        if(node->symbol->type == SYMBOL_IDENTIFIER){
                            fprintf(stdout,"Semantic Error(line %d): '%s' was not declared.\n",node->line,node->symbol->text);
                            error = NOT_DECLARED;
                        }
                        break;
                    }
            case AST_ASSIGN:{
                        if(node->symbol->type == SYMBOL_IDENTIFIER){
                            fprintf(stdout,"Semantic Error(line %d): '%s' was not declared.\n",node->line,node->symbol->text);
                            error = NOT_DECLARED;
                        }
                        break;
                    }
        }//switch(node->type)
        if (undeclaredVerification(node->son[0]) != NO_ERROR) error = NOT_DECLARED;
        if (undeclaredVerification(node->son[1]) != NO_ERROR) error = NOT_DECLARED;
        if (undeclaredVerification(node->son[2]) != NO_ERROR) error = NOT_DECLARED;
        if (undeclaredVerification(node->son[3]) != NO_ERROR) error = NOT_DECLARED;
    }//if(node)
    return error;
}

//######################################################################################################
//######################################################################################################

int useVerification(ast* node){
    int error = NO_ERROR;
    if (node){
        switch(node->type){
            case AST_REF: {
                        if ((node->symbol->type != REF_VARIABLE) && (node->symbol->type != SYMBOL_LIT_INTEGER)){
                            fprintf(stdout,"Semantic Error(line %d): '%s' shouldn't be used as a Variable.\n",node->line,node->symbol->text);
                            error = USE_ERROR;
                        }
                        break;
                    }
            case AST_VEC_USE:{                       
                        if (node->symbol->type != REF_VECTOR){
                            fprintf(stdout,"Semantic Error(line %d): '%s' shouldn't be used as a Vector.\n",node->line,node->symbol->text);
                            error = USE_ERROR;
                        }
                        break;
                    }
            case AST_FUNC_CALL:{
                        if (node->symbol->type != REF_FUNCTION){
                            fprintf(stdout,"Semantic Error(line %d): '%s' shouldn't be used as a Function Call.\n",node->line,node->symbol->text);
                            error = USE_ERROR;
                        }
                        break;
                    }
        }//switch(node->type)
        if (useVerification(node->son[0]) != NO_ERROR) error = USE_ERROR;
        if (useVerification(node->son[1]) != NO_ERROR) error = USE_ERROR;
        if (useVerification(node->son[2]) != NO_ERROR) error = USE_ERROR;
        if (useVerification(node->son[3]) != NO_ERROR) error = USE_ERROR;
    }//if(node)
    return error;
}

//######################################################################################################
//######################################################################################################

void dataTypeDecsVerification(ast* node){
    if (node){
        switch (node->type){
            case AST_VECTDEC:
            case AST_VARDEC:
            case AST_FUNDEC:
            case AST_DECS:{
                        if (node->son[0]->type == AST_INT){
                            node->symbol->dataType = DT_INT;
                            node->dataType = DT_INT;
                        }
                        else{
                            node->symbol->dataType = DT_BYTE;
                            node->dataType = DT_BYTE;
                        }
                        break;
                    }
        }//switch(node->type)
        dataTypeDecsVerification(node->son[0]);
        dataTypeDecsVerification(node->son[1]);
        dataTypeDecsVerification(node->son[2]);
        dataTypeDecsVerification(node->son[3]);
    }//if (node)

}

//######################################################################################################
//######################################################################################################

int dataTypeVerification(ast* node){
    int error = NO_ERROR;
    if (node){
        if (dataTypeVerification(node->son[0]) == DATATYPE_ERROR) error = DATATYPE_ERROR;
        if (dataTypeVerification(node->son[1]) == DATATYPE_ERROR) error = DATATYPE_ERROR;
        if (dataTypeVerification(node->son[2]) == DATATYPE_ERROR) error = DATATYPE_ERROR;
        if (dataTypeVerification(node->son[3]) == DATATYPE_ERROR) error = DATATYPE_ERROR;
        
        switch(node->type){

            case AST_ASSIGN:        { if (checkDataTypeAssign(node) == DATATYPE_ERROR) error = DATATYPE_ERROR; break; }
            case AST_PRINT:         { if (checkDataTypePrint(node) == DATATYPE_ERROR) error = DATATYPE_ERROR; break; }
            case AST_RETURN:        { if (checkDataTypeReturn(node) == DATATYPE_ERROR) error = DATATYPE_ERROR; break; }
            case AST_REF:           { if (checkDataTypeRef(node) == DATATYPE_ERROR) error = DATATYPE_ERROR; break; }
            case AST_VEC_USE:       { if (checkDataTypeVecUse(node) == DATATYPE_ERROR) error = DATATYPE_ERROR; break; }
            case AST_FUNC_CALL:     { if (checkDataTypeFunCall(node) == DATATYPE_ERROR) error = DATATYPE_ERROR; break; }
            case AST_WHILE:         { }
            case AST_IFELSE:        { }
            case AST_IF:            { if (checkDataTypeIf(node) == DATATYPE_ERROR) error = DATATYPE_ERROR; break; }
            case AST_ADD:           { }
            case AST_SUB:           { }
            case AST_MUL:           { }
            case AST_DIV:           { if (checkDataTypeArithmetic(node) == DATATYPE_ERROR) error = DATATYPE_ERROR; break; }
            case AST_LE:            { }
            case AST_GE:            { }
            case AST_EQ:            { }
            case AST_NE:            { }
            case AST_BT:            { }
            case AST_ST:            { if (checkDataTypeCompare(node) == DATATYPE_ERROR) error = DATATYPE_ERROR; break; }
            case AST_AND:           { }
            case AST_OR:            { if (checkDataTypeAndOr(node) == DATATYPE_ERROR) error = DATATYPE_ERROR; break; }
            case AST_ARGS:          { if (checkDataTypeArgs(node) == DATATYPE_ERROR) error = DATATYPE_ERROR; break; }
        }//switch(node->type)    
    }//node
    return error;
}

//######################################################################################################
//######################################################################################################

int argumentsVerification(ast* node){
    ast* funCallArgs;
    ast* funDecArgs;
    int test;
    int error = NO_ERROR;
    if (node){
        if (argumentsVerification(node->son[0]) == ARGUMENT_ERROR) error = ARGUMENT_ERROR;
        if (argumentsVerification(node->son[1]) == ARGUMENT_ERROR) error = ARGUMENT_ERROR;
        if (argumentsVerification(node->son[2]) == ARGUMENT_ERROR) error = ARGUMENT_ERROR;
        if (argumentsVerification(node->son[3]) == ARGUMENT_ERROR) error = ARGUMENT_ERROR;
        
        if (node->type == AST_FUNC_CALL){
            funCallArgs=node->son[0];
            funDecArgs = node->symbol->funDec->son[1];
            
            while(funCallArgs!=NULL && funDecArgs!=NULL){
                
                if ((funCallArgs->son[0]!=NULL) && (funDecArgs->son[0]!=NULL)){
                    if (funCallArgs->son[0]->dataType == DT_BOOLEAN){
                        fprintf(stdout,"Semantic Error(line %d): You can't call a function with a boolean paramether.\n",node->line);
                        error = ARGUMENT_ERROR;
                    }else if (funDecArgs->son[0]->dataType == DT_BOOLEAN){
                        fprintf(stdout,"Semantic Error(line %d): You can't declare a function with a boolean paramether.\n",node->line);
                        error = ARGUMENT_ERROR;
                    }else if (funDecArgs->son[0]->dataType != funCallArgs->son[0]->dataType){
                        if (funCallArgs->son[0]->dataType == DT_INT){
                           fprintf(stdout,"Semantic Warning(line %d): A function paramether doesnt match the type of '%s' in '%s', you might lose data.\n",node->line,funDecArgs->son[0]->symbol->text,node->symbol->text);
                        }
                        else{
                        fprintf(stdout,"Semantic Warning(line %d): A function paramether doesnt match the type of '%s' in '%s', the compiler is performing a cast.\n",node->line,funDecArgs->son[0]->symbol->text,node->symbol->text);
                        }                    
                    }
                }                
                funCallArgs = funCallArgs->son[1];
                funDecArgs  = funDecArgs->son[1];
            }//while
            if (funCallArgs!=NULL){
                fprintf(stdout,"Semantic Error(line %d): You can't call a function with with more paramethers than declared.\n",node->line);
                error = ARGUMENT_ERROR;
            }
            if (funDecArgs!=NULL){
                fprintf(stdout,"Semantic Error(line %d): You can't call a function with with less paramethers than declared.\n",node->line);
                error = ARGUMENT_ERROR;
            }
            
        }// if (AST_FUNC_CALL   
    
    }//if (node)
    return error;
}

//######################################################################################################
//######################################################################################################
//######### THE FUNCTIONS FROM HERE ARE AUXILIAR TO THE PROCESS OF SEMANTIC ANALISIS ###################
//######################################################################################################
//######################################################################################################

//################################# FUNCTIONS FOR dataTypeVerification #################################



int checkDataTypeAssign(ast* node){
    int error=NO_ERROR;
    if (node){
        
        if (node->son[1]){
            
            if ((node->symbol->dataType == DT_BOOLEAN) || (node->son[1]->dataType == DT_BOOLEAN)){
               fprintf(stdout,"Semantic Warning(line %d): You can't assign a boolean expression to a variable.\n",node->line);
               error = DATATYPE_WARN;
            }
            else if (node->son[1]->dataType != node->symbol->dataType)
               fprintf(stdout,"Semantic Warning(line %d): The expression is going to be converted to the type of '%s'.\n",node->line,node->symbol->text);
               error = DATATYPE_WARN;
            }
            
        else{
            if ((node->symbol->dataType == DT_BOOLEAN) || (node->son[0]->dataType == DT_BOOLEAN)){
               fprintf(stdout,"Semantic Warning(line %d): You can't use boolean expressions in assignments.\n",node->line);
               error = DATATYPE_WARN;
            }
            else if (node->son[0]->dataType != node->symbol->dataType){
               fprintf(stdout,"Semantic Warning(line %d): The expression is going to be converted to the type of '%s'.\n",node->line, node->symbol->text);
               error = DATATYPE_WARN;
            }
        }
    }
    return error;
}

int checkDataTypePrint(ast* node){
    int error = NO_ERROR;
    if (node){
        if (node->son[0]){
            if (node->son[0]->dataType == DT_BOOLEAN){
                fprintf(stdout,"Semantic Error(line %d): You can't print a boolean value.\n",node->line);
                error = DATATYPE_ERROR;
            }
        }
    }
    return error;
}

int checkDataTypeReturn(ast* node){
    int error = NO_ERROR;
    if (node){
        if (node->son[0]->dataType == DT_BOOLEAN){
            fprintf(stdout,"Semantic Error(line %d): You can't return a boolean value.\n",node->line);
            error = DATATYPE_ERROR;
        }
    }
    return error;
}

int checkDataTypeRef(ast* node){
    int error = NO_ERROR;
    if (node){
        if (node->symbol->type == SYMBOL_LIT_INTEGER){
            node->symbol->dataType = DT_INT;
            node->dataType = DT_INT;
        }
        else{
            node->dataType = node->symbol->dataType;
        }
    }
    return error;
}

int checkDataTypeVecUse(ast* node){
    int error = NO_ERROR;
    if (node){
        if (node->symbol->dataType == DT_BOOLEAN){
            fprintf(stdout,"Semantic Error(line %d): You can't index a vector with a boolean value.\n",node->line);
            error = DATATYPE_ERROR;
        }
        else{
            node -> dataType = node->symbol->dataType;
        }
    }
    return error;
}

int checkDataTypeFunCall(ast* node){
    ast* argsPtr;
    int error = NO_ERROR;
    if (node){
        argsPtr = node->son[0];
        node->dataType = node->symbol->dataType;
    }
    return error;
}

int checkDataTypeIf(ast* node){
    int error = NO_ERROR;
    if (node){
        if (node->son[0]->dataType != DT_BOOLEAN){
            fprintf(stdout,"Semantic Error(line %d): You must set a boolean expression to be tested.\n",node->line);
            error = DATATYPE_ERROR;
        }
    }
    return error;
}

int checkDataTypeArithmetic(ast* node){
    int error = NO_ERROR;
    if (node){
        if ((node->son[0]->dataType == DT_BOOLEAN) || (node->son[1]->dataType == DT_BOOLEAN)){
            fprintf(stdout,"Semantic Error(line %d): Your sub-expressions must be 'int's or 'Byte's.\n",node->line);
            error = DATATYPE_ERROR;
            node->symbol->dataType = DT_INT;
            node->dataType = DT_INT;
        }
        else if (node->son[0]->dataType != node->son[1]->dataType){
            fprintf(stdout,"Semantic Error(line %d): Your sub-expressions aren't of the same type, you might lose data.\n",node->line);
            error = DATATYPE_WARN;
            node->symbol->dataType = DT_INT;
            node->dataType = DT_INT;
        }
        else{
            node->symbol->dataType = node->son[0]->dataType;
            node->dataType = node->son[0]->dataType;
        }
    }
}

int checkDataTypeCompare(ast* node){
    int error = NO_ERROR;
    if (node){
        if ((node->son[0]->dataType == DT_BOOLEAN) || (node->son[1]->dataType == DT_BOOLEAN)){
            fprintf(stdout,"Semantic Error(line %d): Your sub-expressions must be 'int's or 'Byte's.\n",node->line);
            error = DATATYPE_ERROR;
        }
        else if (node->son[0]->dataType != node->son[1]->dataType){
            fprintf(stdout,"Semantic Warning(line %d): Your sub-expressions aren't of the same type, you might lose data.\n",node->line);
            error = DATATYPE_WARN;
        }
        node->symbol->dataType = DT_BOOLEAN;
        node->dataType = DT_BOOLEAN;
    }
    return error;
}

int checkDataTypeAndOr(ast* node){
    int error = NO_ERROR;
    if (node){
        if ((node->son[0]->dataType != DT_BOOLEAN) || (node->son[1]->dataType != DT_BOOLEAN)){
            fprintf(stdout,"Semantic Error(line %d): Your sub-expressions must be booleans.\n",node->line);
            error = DATATYPE_ERROR;
        }
        node->symbol->dataType = DT_BOOLEAN;
        node->dataType = DT_BOOLEAN;
    }
    return error;
}

int checkDataTypeArgs(ast* node){
    int error = NO_ERROR;
    if (node){
        if (node->son[0]->dataType == DT_BOOLEAN){
            fprintf(stdout,"Semantic Error(line %d): You can't call a function with a boolean argument.\n",node->line);
            error = DATATYPE_ERROR;
        }
    }
    return error;
}





