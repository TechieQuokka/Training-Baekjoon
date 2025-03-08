#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>

struct TreeNodeType {
	
	int Data;
	struct TreeNodeType* Left;
	struct TreeNodeType* Right;
};

bool Insert (struct TreeNodeType* tree, int data);
void Post_Order (struct TreeNodeType* current);

int main (int argc, char* argv[]) {
	
	struct TreeNodeType* tree;
	
	int data = 0;
	scanf ("%d", &data);
	
	tree = (struct TreeNodeType*) calloc (1, sizeof (struct TreeNodeType));
	if (tree == NULL) return -1;
	
	tree->Data = data;
	
	while (scanf("%d", &data) != EOF) {
		
		Insert (tree, data);
	}
	
	Post_Order (tree);
	return 0;
}

void Post_Order (struct TreeNodeType* current) {
	
	if (current == NULL) return;
	
	Post_Order (current->Left);
	Post_Order (current->Right);
	printf ("%d\n", current->Data);
	return;
}

bool Insert (struct TreeNodeType* tree, int data) {
	
	if (tree == NULL) return false;
	
	if (tree->Data > data) {
		
		bool result = Insert (tree->Left, data);
		if (result == false) {
			
			tree->Left = (struct TreeNodeType*) calloc (1, sizeof (struct TreeNodeType));
			if (tree->Left == NULL) return true;
			tree->Left->Data = data;
			return true;
		}
	}
	else {
		
		bool result = Insert (tree->Right, data);
		if (result == false) {
			
			tree->Right = (struct TreeNodeType*) calloc (1, sizeof (struct TreeNodeType));
			if (tree->Right == NULL) return true;
			tree->Right->Data = data;
			return true;
		}
	}
	return true;
}