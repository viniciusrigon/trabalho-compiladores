#ifndef	ASSEMBLER_HEADER
#define ASSEMBLER_HEADER
#include "hash.h"
#include "tacs.h"

extern FILE* outputFile;


void assembler(tac* complete);

void assemblerLabel(tac* tacNode);
void assemblerVectorIndex(tac* tacNode);
void assemblerAssign(tac* tacNode);
void assemblerRead(tac* tacNode);
void assemblerPrintExpression(tac* tacNode);
void assemblerReturn(tac* tacNode);
void assemblerJumpFalse(tac* tacNode);
void assemblerJump(tac* tacNode);
void assemblerAdd(tac* tacNode);
void assemblerSub(tac* tacNode);
void assemblerMul(tac* tacNode);
void assemblerDiv(tac* tacNode);
void assemblerAnd(tac* tacNode);
void assemblerOr(tac* tacNode);
void assemblerLe(tac* tacNode);
void assemblerGe(tac* tacNode);
void assemblerNe(tac* tacNode);
void assemblerEq(tac* tacNode);
void assemblerBt(tac* tacNode);
void assemblerSt(tac* tacNode);
void assemblerFunctionStart(tac* tacNode);
void assemblerFunctionEnd(tac* tacNode);
void assemblerFunctionCall(tac* tacNode);
void assemblerVectorUse(tac* tacNode);
void assemblerPrintString(tac* tacNode);


#endif
