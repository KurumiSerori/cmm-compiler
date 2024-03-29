#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "lib/List.h"
#include "inter-code.h"

static const char *INTER_CODE[] = {
		"LABEL %s :",
		"FUNCTION %s :",
		"%s := %s",
		"%s := %s + %s",
		"%s := %s - %s",
		"%s := %s * %s",
		"%s := %s / %s",
		"GOTO %s",
		"",
		"RETURN %s",
		"",
		"ARG %s",
		"%s := CALL %s",
		"PARAM %s",
		"READ %s",
		"WRITE %s",
};

InterCode* newInterCode(InterCodeKind kind) {
	InterCode* p = (InterCode*)malloc(sizeof(InterCode));
	p->kind = kind;
	p->res = p->op1 = p->op2 = NULL;
	return p;
}

InterCodes* interCodeInsert(InterCodes *head, InterCode *p) {
	assert(head != NULL);
	assert(p != NULL);
	listAddBefore(head, &p->list);
	return head;
}

InterCodes* interCodesBind(InterCodes *first, InterCodes *second) {
	assert(first != NULL);
	assert(second != NULL);
	assert(first != second);
	while (!listIsEmpty(second)) {
		ListHead *p = second->next;
		listDelete(p);
		listAddBefore(first, p);
	}
	return first;
}

#define op2s operandToStr
void interCodeToStr(InterCode* p, char* s) {
	assert(p != NULL);
	assert(s != NULL);
	if (p->kind == GOTO_WITH_COND) {
		sprintf(s, "IF %s %s %s GOTO %s", op2s(p->op1), p->relop, op2s(p->op2), op2s(p->res));
	} else if (p->kind == DEC) {
		sprintf(s, "DEC %s %d", op2s(p->res), p->size);
	} else {
		sprintf(s, INTER_CODE[p->kind], op2s(p->res), op2s(p->op1), op2s(p->op2));
	}
}
#undef op2s

void interCodesPrint(FILE *file, InterCodes *head) {
	assert(file != NULL);
	assert(head != NULL);
	char s[120];
	InterCodes *p;
	listForeach(p, head) {
		InterCode *interCode = listEntry(p, InterCode, list);
		interCodeToStr(interCode, s);
		fprintf(file, "%s\n", s);
	}
}

void test() {
	InterCodes first, second;
	listInit(&first);
	listInit(&second);
	InterCode *ir1 = newInterCode(DEF_FUNCTION);
	ir1->res = newFunctionOperand("func");
	interCodeInsert(&first, ir1);
	InterCode *ir2 = newInterCode(ADD);
	ir2->res = newVarOperand();
	Operand *op = newVarOperand();
	ir2->op1 = deRefOperand(op->id);
	ir2->op2 = constOperand(4);
	interCodeInsert(&first, ir2);
	InterCode *ir3 = newInterCode(ASSIGN);
	ir3->res = addressOperand(ir2->res->id);
	ir3->op1 = constOperand(100);
	interCodeInsert(&second, ir3);
	InterCode *ir4 = newInterCode(DEF_LABEL);
	ir4->res = newLabelOperand();
	interCodeInsert(&second, ir4);
	interCodesBind(&first, &second);
	interCodesPrint(stdout, &first);
}
