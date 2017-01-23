#include "assembler.h"

void assembler(tac* complete)
{
	tac* t = 0;
	hashPrintAssembly(outputFile);
	for (t = complete; t; t = t -> next)
	{
		switch (t->type){
		
		    case    TAC_LABEL:      assemblerLabel(t);break;
		    case    TAC_VEC_IDX:    assemblerVectorIndex(t);break;
		    case    TAC_ASS:        assemblerAssign(t);break;
		    case    TAC_READ:       assemblerRead(t);break;
		    case    TAC_PRINT_EXP:  assemblerPrintExpression(t);break;
		    case    TAC_RETURN:     assemblerReturn(t);break;    
		    case    TAC_JFALSE:     assemblerJumpFalse(t);break;
		    case    TAC_JUMP:       assemblerJump(t);break;
		    case    TAC_ADD:        assemblerAdd(t);break;
		    case    TAC_SUB:        assemblerSub(t);break;
		    case    TAC_MUL:        assemblerMul(t);break;
		    case    TAC_DIV:        assemblerDiv(t);break;
		    case    TAC_AND:        assemblerAnd(t);break;
		    case    TAC_OR:         assemblerOr(t);break;
		    case    TAC_LE:         assemblerLe(t);break;
            case    TAC_GE:         assemblerGe(t);break;
            case    TAC_EQ:         assemblerEq(t);break;
            case    TAC_NE:         assemblerNe(t);break;
            case    TAC_BT:         assemblerBt(t);break;
            case    TAC_ST:         assemblerSt(t);break;
            case    TAC_FUNC_START: assemblerFunctionStart(t);break;
            case    TAC_FUNC_END:   assemblerFunctionEnd(t);break;
            case    TAC_FUNC_CALL:  assemblerFunctionCall(t);break;
            case    TAC_VEC_USE:    assemblerVectorUse(t);break;
            case    TAC_PRINT_STRING: assemblerPrintString(t);break;
		}
	} 
}






void assemblerLabel(tac* tacNode){
	fprintf(outputFile,"%s:\n",tacNode->result->text);
}


void assemblerVectorIndex(tac* tacNode){
    fprintf(outputFile,"\tmovl .%s+%d, %%eax\n"
                        "\tmovl %%eax, .%s\n",
                        tacNode->op1->text,
                        4*atoi(tacNode->op2->text),
                        tacNode->result->text);
}

void assemblerAssign(tac* tacNode){
	fprintf(outputFile,"\tmovl .%s, %%eax\n"
					   "\tmovl %%eax, .%s\n", 
					   tacNode->op1->text,
					   tacNode->result->text);
}

void assemblerRead(tac* tacNode){
    fprintf(outputFile,

                    	"\tmovl $.LC0, %%eax\n"
	                    "\tmovl $.%s, 4(%%esp)\n"
	                    "\tmovl %%eax, (%%esp)\n"
                    	"\tcall __isoc99_scanf\n",
                    	tacNode->result->text);
}

void assemblerPrintExpression(tac* tacNode){

    fprintf(outputFile,
                    	"\tmovl .%s, %%edx\n"
                    	"\tmovl $.LC0, %%eax\n"
	                    "\tmovl %%edx, 4(%%esp)\n"
	                    "\tmovl %%eax, (%%esp)\n"
                    	"\tcall printf\n",
                    	tacNode->result->text);

}

void assemblerReturn(tac* tacNode){
	fprintf(outputFile,"\tmovl .%s, %%eax\n"
					   "\tret \n", 
					   tacNode->result->text);
}

void assemblerJumpFalse(tac* tacNode){
	fprintf(outputFile,"\tmovl .%s, %%eax\n"
					   "\ttst\n"
					   "\tjnz %s\n",
					   tacNode->op1->text,
					   tacNode->result->text);
}

void assemblerJump(tac* tacNode){
	fprintf(outputFile,  "\tjmp %s\n",
						tacNode->result->text);
}

void assemblerAdd(tac* tacNode){		
	fprintf(outputFile, "\tmovl .%s, %%eax\n"
	                    "\tadd .%s, %%eax\n"
	                    "\tmovl %%eax, .%s\n",
	                     tacNode->op1->text, 
	                     tacNode->op2->text,
	                     tacNode->result->text);
}

void assemblerSub(tac* tacNode){		
	fprintf(outputFile, "\tmovl .%s, %%eax\n"
	                    "\tsub .%s, %%eax\n"
	                    "\tmovl %%eax, .%s\n",
	                    tacNode->op1->text,
	                    tacNode->op2->text,
	                    tacNode->result->text);	
}

void assemblerMul(tac* tacNode){	
	fprintf(outputFile, "\tmovl .%s, %%eax\n"
	                    "\tmovl .%s, %%edx\n"
	                    "\timull %%edx, %%eax\n"
	                    "\tmovl %%eax, .%s\n",
	                    tacNode->op1->text,
	                    tacNode->op2->text,
	                    tacNode->result->text);	
}

void assemblerDiv(tac* tacNode){		
	fprintf(outputFile, "\tmovl .%s, %%eax\n"
	                    "\tmovl .%s, %%ebx\n"
	                    "\tidiv %%eax\n"
	                    "\tmov %%dx, .%s\n",
	                    tacNode->op1->text,
	                    tacNode->op2->text,
	                    tacNode->result->text);	
}

void assemblerAnd(tac* tacNode){
	
}

void assemblerOr(tac* tacNode){

}

void assemblerLe(tac* tacNode){

}

void assemblerGe(tac* tacNode){

}

void assemblerNe(tac* tacNode){

}

void assemblerEq(tac* tacNode){

}

void assemblerBt(tac* tacNode){

}

void assemblerSt(tac* tacNode){

}

void assemblerFunctionStart(tac* tacNode){
	fprintf(outputFile, 
						"\n.globl %s\n"
						"\t.type %s,@function\n"
						"%s:\n"
						"\tpushl %%ebp\n"
						"\tmovl %%esp, %%ebp\n"
						"\tandl $-16, %%esp\n"
                    	"\tsubl $16, %%esp\n",
					   tacNode->result->text,
					   tacNode->result->text,
					   tacNode->result->text);
}

void assemblerFunctionEnd(tac* tacNode){
	fprintf(outputFile,
						"\tleave\n"
						"\tret\n");
}

void assemblerFunctionCall(tac* tacNode){
	fprintf(outputFile,
						"\tcall %s"
						"\tmovl %%eax %s",
						tacNode->op1->text,
						tacNode->result->text);
}

void assemblerVectorUse(tac* tacNode){
  
}

void assemblerPrintString(tac* tacNode){
    fprintf(outputFile,
                        
                    	"\tmovl $%s, %%eax\n"
	                    "\tmovl %%eax, (%%esp)\n"
                    	"\tcall printf\n",
                    	tacNode->result->text);
}

