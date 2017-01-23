#include "tacs.h"

tac* tacJoin(tac* list1, tac* list2){
    tac* iterator = 0;
	if (!list1){
		return list2;
	}
	if (!list2){
		return list1;
	}
	iterator = list1;
	for (iterator; iterator->prev; iterator=iterator->prev) ;
	iterator->prev=list2;
	return list1;

}

tac* tacCreate(int type, hashNode* symbol, hashNode* op1, hashNode* op2){
	tac* newTacNode = calloc(1,sizeof(tac));	
	newTacNode->type = type;	
	newTacNode->result = symbol;
	newTacNode->op1 = op1;
	newTacNode->op2 = op2;
	newTacNode->prev = 0;
	newTacNode->next = 0;	
	return newTacNode;	
}

void tacPrint(tac* t1){	
	if (t1){
		fprintf(stdout,"[Tipo: %s,",printTypes(t1->type));
		fprintf(stdout," res: %s,",(t1->result && t1->result->text) ? t1->result->text:" ");
		fprintf(stdout," op1: %s,",(t1->op1 && t1->op1->text) ? t1->op1->text:" ");
		fprintf(stdout," op2: %s]\n",(t1->op2 && t1->op2->text)? t1->op2->text:" ");
		tacPrint(t1->next);		
	}
	
}

char* printTypes(int type){
	switch(type){
		case TAC_LABEL: {return "TAC_LABEL";}
		case TAC_NOP: {return "TAC_NOP";}
		case TAC_VEC_IDX: {return "TAC_VEC_IDX";}
		case TAC_ASS: {return "TAC_ASS";}
		case TAC_READ: {return "TAC_READ";}
		case TAC_PRINT_EXP: {return "TAC_PRINT_EXP";}
		case TAC_RETURN: {return "TAC_RETURN";}
		case TAC_JFALSE: {return "TAC_JFALSE";}
		case TAC_JUMP: {return "TAC_JUMP";}
		case TAC_REF: {return "TAC_REF";}
		case TAC_ADD: {return "TAC_ADD";}
		case TAC_SUB: {return "TAC_SUB";}
		case TAC_MUL: {return "TAC_MUL";}
		case TAC_DIV: {return "TAC_DIV";}
		case TAC_AND: {return "TAC_AND";}
		case TAC_OR: {return "TAC_OR";}
		case TAC_LE: {return "TAC_LE";}
		case TAC_GE: {return "TAC_GE";}
		case TAC_EQ: {return "TAC_EQ";}
		case TAC_NE: {return "TAC_NE";}
		case TAC_BT: {return "TAC_BT";}
		case TAC_ST: {return "TAC_ST";}
		case TAC_FUNC_START: {return "TAC_FUNC_START";}
		case TAC_FUNC_END  : {return "TAC_FUNC_END";}
		case TAC_FUNC_CALL: {return "TAC_FUNC_CALL";}
		case TAC_VEC_USE: {return "TAC_VEC_USE";}

		case TAC_PRINT_STRING: {return "TAC_PRINT_STRING";}
		default:			{return "TAC_UNKNOWN";}
	
	}
}



tac* tacReverse(tac* tacs){
	tac* iterator;
	iterator = tacs;
	while(iterator->prev){
		iterator->prev->next = iterator;
		iterator = iterator->prev;
	}
	return iterator;
}

tac* generateCode(ast* node){
	int i = 0;
	tac* sonTac[AST_MAX_SONS];
	
	if (node){
		for (i = 0;i<AST_MAX_SONS;i++){
			sonTac[i] = generateCode(node->son[i]);
		}
		
		switch(node->type){
			case AST_ADD:		{ return generateBinOp(TAC_ADD,node,sonTac); break;}
			case AST_SUB:		{ return generateBinOp(TAC_SUB,node,sonTac); break;}
			case AST_MUL: 		{ return generateBinOp(TAC_MUL,node,sonTac); break;}
			case AST_DIV:		{ return generateBinOp(TAC_DIV,node,sonTac); break;}
			case AST_AND: 		{ return generateBinOp(TAC_AND,node,sonTac); break;}
			case AST_OR:		{ return generateBinOp(TAC_OR,node,sonTac); break;}
			case AST_LE:		{ return generateBinOp(TAC_LE,node,sonTac); break;}
			case AST_GE:		{ return generateBinOp(TAC_GE,node,sonTac); break;}
			case AST_EQ:		{ return generateBinOp(TAC_EQ,node,sonTac); break;}
			case AST_NE:		{ return generateBinOp(TAC_NE,node,sonTac); break;}
			case AST_BT :		{ return generateBinOp(TAC_BT,node,sonTac); break;}	
			case AST_ST :		{ return generateBinOp(TAC_ST,node,sonTac); break;}
			case AST_FUNC_CALL:	{ return generateFunCall(node,sonTac); break;}
			case AST_WHILE:		{ return generateWhile(node,sonTac); break;}
			case AST_IF:		{ return generateIf(node,sonTac); break;}
			case AST_IFELSE:	{ return generateIfElse(node,sonTac); break;}
			case AST_RETURN:	{ return generateReturn(node,sonTac); break;}
			case AST_PRINT:		{ return generatePrint(node,sonTac); break;}
			case AST_READ:		{ return generateRead(node,sonTac); break;}        
			case AST_ASSIGN:	{ return generateAss(node,sonTac); break;}      
			case AST_EPTCMD:	{ return generateEmptyCmd(node,sonTac); break;}      
			case AST_COMMANDS:	{ return generateCommands(node,sonTac); break;}    
			case AST_COMBLK:	{ return generateCmdBlk(node,sonTac); break;}           
			case AST_FUNDEC:	{ return generateFunDec(node,sonTac); break;}      
			case AST_DECL:		{ return generateDecList(node,sonTac);break;}
            case AST_VEC_USE:   { return generateVecUse(node,sonTac); break;}      
			case AST_REF:   	{ return generateRef(node,sonTac);break;}
			default:            {return 0;break;}
		} //switch
	}// if
	
} // generate code()


//###########################################################################################
tac* generateDecList(ast* node, tac** sonTac){
	return tacJoin(sonTac[1], sonTac[0]);
}

//###########################################################################################
tac* generateFunDec(ast* node, tac** sonTac){
	tac *func,*label = 0;
	label = tacCreate(TAC_FUNC_START, node->symbol, 0, 0);
	func = tacJoin(sonTac[2],label);
	label = tacCreate(TAC_FUNC_END, 0, 0, 0);
	func = tacJoin(label,func);
	return func;
}

//###########################################################################################
tac* generateCmdBlk(ast* node, tac** sonTac){
	return sonTac[0];
}

//###########################################################################################
tac* generateCommands(ast* node, tac** sonTac){
	return tacJoin(sonTac[1], sonTac[0]);
}

//###########################################################################################
tac* generateEmptyCmd(ast* node, tac** sonTac){
	return tacCreate(TAC_NOP, 0, 0, 0);
}

//###########################################################################################
tac* generateAss(ast* node, tac** sonTac){
	tac *ass, *address = 0;
	if (node->son[1]){
		address = tacCreate(TAC_VEC_IDX, hashMakeTemp(), node->symbol, sonTac[0]->result);
		address = tacJoin(address, sonTac[0]);
		address = tacJoin(address,sonTac[1]);
		ass = tacCreate(TAC_ASS, address->result, sonTac[1]->result, 0);
		ass = tacJoin(ass,address);
		return ass;
	}
	else{
		ass = tacCreate(TAC_ASS, node->symbol, sonTac[0]->result, 0);
		return tacJoin(ass,sonTac[0]);
	}
}

//###########################################################################################
tac* generateRead(ast* node, tac** sonTac){
	return tacCreate(TAC_READ, node->symbol, 0, 0);
}

//###########################################################################################
tac* generatePrint(ast* node, tac** sonTac){
	tac* print;
	if (node->son[0]){ //print exp
		print = tacCreate(TAC_PRINT_EXP, sonTac[0]->result, 0, 0);
		return tacJoin(print, sonTac[0]);
	}
	else{
		return tacCreate(TAC_PRINT_STRING, node->symbol, 0, 0);
	}
}

//###########################################################################################
tac* generateReturn(ast* node, tac** sonTac){
	tac* ret;
	ret = tacCreate(TAC_RETURN, sonTac[0]->result, 0, 0);
	return tacJoin(ret, sonTac[0]);
}

//###########################################################################################
tac* generateIf(ast* node, tac** sonTac){
	tac* JFalse, *Cmd, *label;
	JFalse = tacCreate(TAC_JFALSE, makeLabel(), sonTac[0]->result, 0);
	JFalse = tacJoin(JFalse, sonTac[0]);
	Cmd = sonTac[1];
	Cmd = tacJoin(Cmd, JFalse);
	label = tacCreate(TAC_LABEL, JFalse->result, 0, 0);
	return tacJoin(label, Cmd);
}

//###########################################################################################
tac* generateIfElse(ast* node, tac** sonTac){
	tac* JFalse, *Cmd, *labelFalse, *JumpEndTrue, *labelEndFalse;
	JFalse = tacCreate(TAC_JFALSE, makeLabel(), sonTac[0]->result, 0);
	JFalse = tacJoin(JFalse, sonTac[0]);
	
	Cmd = sonTac[1];
	Cmd = tacJoin(Cmd, JFalse);
	
	JumpEndTrue = tacCreate(TAC_JUMP, makeLabel(), 0, 0);
	JumpEndTrue = tacJoin(JumpEndTrue, Cmd);
		
	labelFalse = tacCreate(TAC_LABEL, JFalse->result, 0, 0);
	labelFalse = tacJoin(labelFalse, JumpEndTrue);
	labelFalse = tacJoin(sonTac[2], labelFalse);
	
	labelEndFalse = tacCreate(TAC_LABEL, JumpEndTrue->result, 0, 0);
	
	return tacJoin(labelEndFalse, labelFalse);
}

//###########################################################################################
tac* generateWhile(ast* node, tac** sonTac){
	tac *labelStartWhile, *While, *JFalse, *exp, *labelEndWhile, *JumpEndWhile;
	
	labelStartWhile = tacCreate(TAC_LABEL, makeLabel(), 0, 0);
	
	exp = tacJoin(sonTac[0], labelStartWhile);
	
	JFalse = tacCreate(TAC_JFALSE, makeLabel(), exp->result, 0);
	
	While = tacJoin(JFalse, exp);
	
	While = tacJoin(sonTac[1], While);
	
	JumpEndWhile = tacCreate(TAC_JUMP, labelStartWhile->result, 0, 0);
	
	JumpEndWhile = tacJoin(JumpEndWhile, While);
	
	labelEndWhile = tacCreate(TAC_LABEL, JFalse->result, 0, 0);
	
	return tacJoin(labelEndWhile, JumpEndWhile);	
}

//###########################################################################################
tac* generateBinOp(int opCode, ast* node, tac** sonTac){
	tac* operation,*joinExps;
	operation = tacCreate(opCode, node->symbol, sonTac[0]->result, sonTac[1]->result);
	joinExps = tacJoin(sonTac[1], sonTac[0]);
	operation = tacJoin(operation,joinExps);
	return operation;
}

//###########################################################################################
tac* generateRef(ast* node, tac** sonTac){
	return tacCreate(TAC_REF, node->symbol, 0, 0);
}

//###########################################################################################
tac* generateFunCall(ast* node, tac** sonTac){
	tac* funcCall,*args;
	sonTac[0] = generateArgs(node,sonTac);
	funcCall =  tacCreate(TAC_FUNC_CALL, node->symbol, 0, 0);
	return tacJoin(funcCall,sonTac[0]);
}

//###########################################################################################
tac* generateArgs(ast* node, tac** sonTac){
	tac *newAssign,*allAssigns;
	ast* funcVarDec;
	ast* funcSetArg;
	funcVarDec = node->symbol->funDec->son[1];
	funcSetArg=node->son[0];
	allAssigns=0;
	while((funcVarDec) && (funcSetArg)){
		if ((funcVarDec->son[0]) && (funcSetArg->son[0])){
			newAssign = tacCreate(TAC_ASS, funcVarDec->son[0]->symbol, funcSetArg->son[0]->symbol ,0);
			allAssigns = tacJoin(newAssign,allAssigns);
		
		}
		funcVarDec = funcVarDec->son[1];
		funcSetArg = funcSetArg->son[1];
	}
	return allAssigns;
	

}

//###########################################################################################
tac* generateVecUse(ast* node, tac** sonTac){
	tac* address;
	address = tacCreate(TAC_VEC_IDX, hashMakeTemp(), node->symbol, sonTac[0]->result);
	return tacJoin(address,sonTac[0]);

}

tac* generateVec(ast* node, tac** sonTac){
	return tacCreate(TAC_VEC_USE, node->symbol, 0, 0);
}
