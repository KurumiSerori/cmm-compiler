#include <stdio.h>
#include "syntax-tree.h"
#include "translate.h"
#include "symbol.h"

void yyrestart(FILE*);
void yyparse();
void print(TreeNode*, int);
void test();

void init() {
	symbolTableInit();
	typesInit();
	interCodesInit();
//	test();
}

int main(int argc, char* argv[]) {
	if (argc <= 1) return 1;
	FILE *f = fopen(argv[1], "r");
	if (!f) return 1;
	init();
	yyrestart(f);
	yyparse();
	if (root != NULL) {
//		print(root, 0);
		analyseProgram(root);
		InterCodes *head = interCodesGet();
		interCodesPrint(stdout, head);
	}
	return 0;
}
