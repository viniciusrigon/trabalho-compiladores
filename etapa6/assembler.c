#include "assembler.h"
int jumpLabelNumber = 0;
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
    fprintf(outputFile,"\tmovl (.%s+%d), %%eax\n"
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
				"\tpopl %%ebp\n"
					   "\tret \n", 
					   tacNode->result->text);
}

void assemblerJumpFalse(tac* tacNode){
	fprintf(outputFile,"\tmovl .%s, %%eax\n"
					   "\ttestl %%eax,%%eax\n"
					   "\tjz %s\n",
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
	fprintf(outputFile, "\tmovl .%s, %%eax\n"
	                    "\tmovl .%s, %%ebx\n"
	                    "\tand %%ebx, %%eax\n"
	                    "\tmov %%eax, .%s\n",
	                    tacNode->op1->text,
	                    tacNode->op2->text,
	                    tacNode->result->text);
}

void assemblerOr(tac* tacNode){
	fprintf(outputFile, "\tmovl .%s, %%eax\n"
	                    "\tmovl .%s, %%ebx\n"
	                    "\tor %%ebx, %%eax\n"
	                    "\tmov %%eax, .%s\n",
	                    tacNode->op1->text,
	                    tacNode->op2->text,
	                    tacNode->result->text);

}

void assemblerLe(tac* tacNode){
	fprintf(outputFile,"\tmovl .%s, %%edx\n"
			   "\tmovl .%s, %%eax\n"
			   "\tcmpl %%eax, %%edx\n"
			   "\tjle .LABELJLE%d\n"
			   "\tmovl $0, %%eax\n"
			   "\tjmp .LABELJLEEND%d\n"
			   ".LABELJLE%d:\n"
			   "\tmovl $1, %%eax\n"
			   ".LABELJLEEND%d:\n"
			   "\tmovl %%eax, .%s\n",
			tacNode->op1->text, 
			tacNode->op2->text, 
			jumpLabelNumber, 
			jumpLabelNumber, 
			jumpLabelNumber, 
			jumpLabelNumber,
			tacNode->result->text);
	jumpLabelNumber++;

}

void assemblerGe(tac* tacNode){
	fprintf(outputFile,"\tmovl .%s, %%edx\n"
			   "\tmovl .%s, %%eax\n"
			   "\tcmpl %%eax, %%edx\n"
			   "\tjge .LABELJGE%d\n"
			   "\tmovl $0, %%eax\n"
			   "\tjmp .LABELJGEEND%d\n"
			   ".LABELJGE%d:\n"
			   "\tmovl $1, %%eax\n"
			   ".LABELJGEEND%d:\n"
			   "\tmovl %%eax, .%s\n",
			tacNode->op1->text, 
			tacNode->op2->text, 
			jumpLabelNumber, 
			jumpLabelNumber, 
			jumpLabelNumber, 
			jumpLabelNumber,
			tacNode->result->text);
	jumpLabelNumber++;

}

void assemblerNe(tac* tacNode){
	fprintf(outputFile,"\tmovl .%s, %%edx\n"
			   "\tmovl .%s, %%eax\n"
			   "\tcmpl %%eax, %%edx\n"
			   "\tjne .LABELJNE%d\n"
			   "\tmovl $0, %%eax\n"
			   "\tjmp .LABELJNEEND%d\n"
			   ".LABELJNE%d:\n"
			   "\tmovl $1, %%eax\n"
			   ".LABELJNEEND%d:\n"
			   "\tmovl %%eax, .%s\n",
			tacNode->op1->text, 
			tacNode->op2->text, 
			jumpLabelNumber, 
			jumpLabelNumber, 
			jumpLabelNumber, 
			jumpLabelNumber,
			tacNode->result->text);
	jumpLabelNumber++;

}

void assemblerEq(tac* tacNode){
	fprintf(outputFile,"\tmovl .%s, %%edx\n"
			   "\tmovl .%s, %%eax\n"
			   "\tcmpl %%eax, %%edx\n"
			   "\tje .LABELJEQ%d\n"
			   "\tmovl $0, %%eax\n"
			   "\tjmp .LABELJEQEND%d\n"
			   ".LABELJEQ%d:\n"
			   "\tmovl $1, %%eax\n"
			   ".LABELJEQEND%d:\n"
			   "\tmovl %%eax, .%s\n",
			tacNode->op1->text, 
			tacNode->op2->text, 
			jumpLabelNumber, 
			jumpLabelNumber, 
			jumpLabelNumber, 
			jumpLabelNumber,
			tacNode->result->text);
	jumpLabelNumber++;

}

void assemblerBt(tac* tacNode){
	fprintf(outputFile,"\tmovl .%s, %%edx\n"
			   "\tmovl .%s, %%eax\n"
			   "\tcmpl %%eax, %%edx\n"
			   "\tjg .LABELJG%d\n"
			   "\tmovl $0, %%eax\n"
			   "\tjmp .LABELJGEND%d\n"
			   ".LABELJG%d:\n"
			   "\tmovl $1, %%eax\n"
			   ".LABELJGEND%d:\n"
			   "\tmovl %%eax, .%s\n",
			tacNode->op1->text, 
			tacNode->op2->text, 
			jumpLabelNumber, 
			jumpLabelNumber, 
			jumpLabelNumber, 
			jumpLabelNumber,
			tacNode->result->text);
	jumpLabelNumber++;

}

void assemblerSt(tac* tacNode){
fprintf(outputFile,"\tmovl .%s, %%edx\n"
			   "\tmovl .%s, %%eax\n"
			   "\tcmpl %%eax, %%edx\n"
			   "\tjl .LABELJL%d\n"
			   "\tmovl $0, %%eax\n"
			   "\tjmp .LABELJLEND%d\n"
			   ".LABELJL%d:\n"
			   "\tmovl $1, %%eax\n"
			   ".LABELJLEND%d:\n"
			   "\tmovl %%eax, .%s\n",
			tacNode->op1->text, 
			tacNode->op2->text, 
			jumpLabelNumber, 
			jumpLabelNumber, 
			jumpLabelNumber, 
			jumpLabelNumber,
			tacNode->result->text);
	jumpLabelNumber++;

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
						"\tleave\n""\tpopl %%ebp\n"
						"\tret\n");
}

void assemblerFunctionCall(tac* tacNode){
	fprintf(outputFile,
						"\tcall %s\n"
						"\tmovl %%eax, .%s\n",
						tacNode->op1->text,
						tacNode->result->text);
}

void assemblerVectorUse(tac* tacNode){
	fprintf(outputFile,
			"\tmovl .%s, %%eax\n"
			"\tmovl .%s, %%ebx\n"
			"\tmovl %%ebx, .%s(,%%eax,4)\n",
			tacNode->op1->text,
			tacNode->op2->text,
			tacNode->result->text);
  
}

void assemblerPrintString(tac* tacNode){
    fprintf(outputFile,
                        
                    	"\tmovl $%s, %%eax\n"
	                "\tmovl %%eax, (%%esp)\n"
                    	"\tcall printf\n",
                    	tacNode->result->text);
}

