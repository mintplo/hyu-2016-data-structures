#define _CRT_SECURE_NO_WARNINGS
#define MAX(x, y) ( ((x) > (y)) ? (x) : (y) )

#include <stdio.h>

typedef int ElementType;
typedef struct avlNode* Position;
typedef struct avlNode* AVLTree;
struct avlNode {
	ElementType element;
	AVLTree left;
	AVLTree right;
	int height;
};

Position singleRotateWithLeft(Position node);
Position singleRotateWithRight(Position node);
Position doubleRotateWithLeft(Position node);
Position doubleRotateWithRight(Position node);
AVLTree insert(AVLTree tree, ElementType element);
int height(Position p);
void printInorder(AVLTree tree);

void main(int argc, char** argv) {
	AVLTree tree = NULL;
	FILE* fp;
	int cmdValue;

	fp = fopen(argv[1], "r");

	while (!feof(fp)) {
		fscanf(fp, "%d", &cmdValue);

		tree = insert(tree, cmdValue);
	}

	printf("===== print inorder \n");
	printInorder(tree);
	printf("\n===== end\n");
}

Position singleRotateWithLeft(Position node) {
	Position temp = node->left;

	node->left = temp->right;
	temp->right = node;

	node->height = MAX(height(node->left), height(node->right)) + 1;
	temp->height = MAX(height(temp->left), node->height);

	return temp;
}

Position singleRotateWithRight(Position node) {
	Position temp = node->right;

	node->right = temp->left;
	temp->left = node;

	node->height = MAX(height(node->left), height(node->right)) + 1;
	temp->height = MAX(node->height, height(temp->right)) + 1;

	return temp;
}

Position doubleRotateWithLeft(Position node) {
	node->left = singleRotateWithRight(node->left);

	return singleRotateWithLeft(node);
}

Position doubleRotateWithRight(Position node) {
	node->right = singleRotateWithLeft(node->right);

	return singleRotateWithRight(node);
}

AVLTree insert(AVLTree tree, ElementType element) {
	if (!tree) {
		tree = (AVLTree)malloc(sizeof(struct avlNode));
		if (tree) {
			tree->left = tree->right = NULL;
			tree->element = element;
			tree->height = 0;
		}
		else {
			fprintf(stderr, "Insertion Failed: out of memory");

			return NULL;
		}
	}
	else if (element < tree->element) {
		tree->left = insert(tree->left, element);
		if ((height(tree->left) - height(tree->right)) == 2) {
			if (element < tree->left)
				tree = singleRotateWithLeft(tree);
			else
				tree = doubleRotateWithRight(tree);
		}
	}
	else if (element >= tree->element) {
		tree->right = insert(tree->right, element);
		if ((height(tree->right) - height(tree->left)) == 2) {
			if (element > tree->right)
				tree = singleRotateWithRight(tree);
			else
				tree = doubleRotateWithRight(tree);
		}
	}
	tree->height = MAX(height(tree->left), height(tree->right)) + 1;

	return tree;
}

int height(Position p) {
	if (!p)
		return -1;
	else
		p->height;
}

void printInorder(AVLTree tree) {
	if (tree) {
		printInorder(tree->left);
		printf("%3d", tree->element);
		printInorder(tree->right);
	}
}
