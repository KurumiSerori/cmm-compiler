#include "symbol.h"
#include <stdio.h>
void yyrestart(FILE*);
void yyparse();
int main(int argc, char* argv[]) {
    symbolTableInit();
	typesInit();
	if (argc <= 1) return 1;
	FILE *f = fopen(argv[1], "r");
	if (!f) return 1;
	yyrestart(f);
	yyparse();
	return 0;
}
