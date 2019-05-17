#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct tree* PtrToNode;
typedef struct tree* Tree;
struct tree {
	ElementType element;
	PtrToNode left;
	PtrToNode right;
};

Tree insertNode(Tree r, ElementType e);
Tree deleteNode(Tree r, ElementType e);
Tree findNode(Tree r, ElementType e);
Tree findMin(Tree r);
Tree findMax(Tree r);

void printInorder(Tree r);
void printPreorder(Tree r);
void printPostorder(Tree r);

void main(int argc, char** argv) {
	Tree r = NULL;
	Tree result = NULL;
	FILE* fr = NULL;
	char cmd;
	int temp;

	fr = fopen(argv[1], "r");

	while (!feof(fr)) {
		cmd = fgetc(fr);

		switch (cmd) {
		case 'i':
			fscanf(fr, "%d\n", &temp);
			r = insertNode(r, temp);
			break;
		case 'd':
			fscanf(fr, "%d\n", &temp);
			r = deleteNode(r, temp);
			break;
		case 'f':
			fscanf(fr, "%d\n", &temp);
			result = findNode(r, temp);
			printf("%d is %sin the tree\n", temp, (result) ? "" : "not ");
			break;
		case 'p':
			cmd = fgetc(fr);
			if (cmd == 'i') {
				printf("Inorder: ");
				printInorder(r);
			}
			else if (cmd == 'r') {
				printf("Preorder: ");
				printPreorder(r);
			} else {
				printf("Postorder: ");
				printPostorder(r);
			}

			fgetc(fr); // remove \n
			printf("\n");
			break;
		default:
			break;
		}
	}
}

Tree insertNode(Tree r, ElementType e) {
	if (r == NULL) {
		r = (Tree)malloc(sizeof(struct tree));
		r->element = e;
		r->left = r->right = NULL;
	}
	else if (r->element > e) {
		r->left = insertNode(r->left, e);
	}
	else if (r->element < e) {
		r->right = insertNode(r->right, e);
	}
	// 중복 엘리먼트는 취급 X

	return r;
}

Tree deleteNode(Tree r, ElementType e) {
	Tree temp;

	if (r == NULL) {
		return NULL;
	}
	else if (r->element > e) {
		r->left = deleteNode(r->left, e);
	}
	else if (r->element < e) {
		r->right = deleteNode(r->right, e);
	}
	else if (r->left && r->right) {
		temp = findMin(r->right);
		r->element = temp->element;
		r->right = deleteNode(r->right, r->element);
	}
	else {
		temp = r;
		if (r->left == NULL) {
			r = r->right;
		}
		else if (r->right == NULL) {
			r = r->left;
		}

		free(temp);
	}

	return r;
}

Tree findNode(Tree r, ElementType e) {
	if (r == NULL) {
		return NULL;
	}

	if (r->element > e) {
		r = findNode(r->left, e);
	}
	else if (r->element < e) {
		r = findNode(r->right, e);
	}

	return r;
}

Tree findMin(Tree r) {
	if (r->left == NULL) {
		return r;
	}

	return findMin(r->left);
}

Tree findMax(Tree r) {
	if (r->right == NULL) {
		return r;
	}

	return findMax(r->right);
}

void printInorder(Tree r) {
	if (r == NULL) {
		return;
	}
	else {
		printInorder(r->left);
		printf("%3d", r->element);
		printInorder(r->right);
	}
}

void printPreorder(Tree r) {
	if (r == NULL) {
		return;
	}
	else {
		printf("%3d", r->element);
		printPreorder(r->left);
		printPreorder(r->right);
	}
}

void printPostorder(Tree r) {
	if (r == NULL) {
		return;
	}
	else {
		printPostorder(r->left);
		printPostorder(r->right);
		printf("%3d", r->element);
	}
}
