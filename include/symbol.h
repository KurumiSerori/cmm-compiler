#ifndef COMPILER_SYMBOL_H
#define COMPILER_SYMBOL_H
#include <stdbool.h>
#include "lib/List.h"
#include "syntax-tree.h"

typedef enum { BASIC, ARRAY, STRUCTURE } TypeKind;
typedef enum { VAR, STRUCT, FUNC } SymbolKind;
typedef struct Type {
	TypeKind kind;
	union {
		int basic;
		struct { struct Type *elem; int size; } array;
		ListHead structure;
	};
} Type;
typedef struct Field {
	char* name;
	Type* type;
	ListHead list;
} Field;
typedef struct Func {
	Type* retType;
	ListHead args;
	bool defined;
} Func;
typedef Field Arg;

extern Type *TYPE_INT, *TYPE_FLOAT;
void typesInit();
bool typeEqual(Type*, Type*);
bool argsEqual(ListHead*, ListHead*);
bool funcEqual(Func*, Func*);
void releaseArgs(ListHead* args);
void releaseFunc(Func*);
void typeToStr(Type*, char*);
void argsToStr(ListHead*, char*);
Field* fieldFind(ListHead*, const char*);

typedef struct Symbol {
	char* name;
	SymbolKind kind;
	union {
		Type* type;
		Func* func;
	};
	int depth;
} Symbol;

void symbolTableInit();
void symbolsStackPush();
void symbolsStackPop();
bool symbolAtStackTop(const char*);

bool symbolInsert(Symbol*);
Symbol* symbolFind(const char*);

void analyseProgram(TreeNode*);

#endif
