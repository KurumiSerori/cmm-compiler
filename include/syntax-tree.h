#ifndef __LIB_NODE_H__
#define __LIB_NODE_H__

#include "lib/List.h"

typedef struct TreeNode {
	bool isToken;
	int lineNo, token;
	union {
		int intVal;
		float floatVal;
	};
	char *text, *name;
	ListHead list, children;
} TreeNode;

extern TreeNode *root;

TreeNode* newNode();
void treeAddChild(TreeNode*, TreeNode*);
bool treeIsLeaf(TreeNode*);
TreeNode* treeFirstChild(TreeNode*);
TreeNode* treeLastChild(TreeNode*);
TreeNode* treeKthChild(TreeNode*, int);

#endif