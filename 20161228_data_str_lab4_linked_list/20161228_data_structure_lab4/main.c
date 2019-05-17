#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef enum { TRUE = 1, FALSE = 0 } Boolean;
typedef struct Node* PtrToNode;
typedef PtrToNode Stack;
struct Node {
	char Element;
	PtrToNode Next;
};

Stack createStack(Stack s);
Boolean isEmpty(Stack s);
char pop(Stack s);
char top(Stack s);
void push(Stack s, char value);
void printStack(Stack s);

Boolean isNumeric(char element);
Boolean isSameOrLowerThanTop(char prevOp, char op);
int getOperatorPrecedence(char op);
void doOperatorPrintUntilBigger(Stack s, char op);

void main(int argc, char** argv) {
	FILE* fr = NULL;
	Stack s = NULL;
	char *buffer = (char*)malloc(sizeof(char) * 100);
	char *temp, prevOp;

	s = createStack(s);

	temp = buffer;
	fr = fopen(argv[1], "r");
	fgets(buffer, 100, fr);

	while (*temp != '#') {
		if (isNumeric(*temp)) {
			printf("%d", atoi(temp++));

			continue;
		}

		doOperatorPrintUntilBigger(s, *temp);
		if (*temp != ')') {
			push(s, *temp);
		}
		
		temp++;
	}
}

Stack createStack(Stack s) {
	s = (Stack)malloc(sizeof(struct Node));

	if (s == NULL) {
		fprintf(stderr, "Out of Memory!");
		exit(EXIT_FAILURE);
	}

	s->Next = NULL;
	s->Element = '0';

	return s;
}

Boolean isEmpty(Stack s) {
	return s->Next == NULL;
}

char pop(Stack s) {
	char cTemp;
	PtrToNode temp = s->Next;

	if (isEmpty(s)) {
		fprintf(stderr, "Pop Failed: Stack is Empty!");
		return -1;
	}

	s->Next = s->Next->Next;
	cTemp = temp->Element;
	free(temp);

	return cTemp;
}

char top(Stack s) {
	if (isEmpty(s)) {
		fprintf(stderr, "Top Failed: Stack is Empty!");
		return -1;
	}

	return s->Next->Element;
}

void push(Stack s, char e) {
	PtrToNode temp = (PtrToNode)malloc(sizeof(struct Node));
	if (temp == NULL) {
		fprintf(stderr, "Push Failed: Out of Memory");
	}

	temp->Element = e;
	temp->Next = s->Next;
	s->Next = temp;
}

void printStack(Stack s) {
	PtrToNode p = s->Next;

	printf("\n ==== Stack Top ==== \n");
	while (p != NULL) {
		printf("|%3c|\n", p->Element);
		p = p->Next;
	}
	printf(" ==== Stack Bottom ==== \n");
}

Boolean isNumeric(char element) {
	switch (element) {
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case '(':
	case ')':
		return 0;
	default:
		return 1;
	}
}

void doOperatorPrintUntilBigger(Stack s, char op) {
	char prevOp;

	while (!isEmpty(s)) {
		prevOp = top(s);

		if (op != ')') {
			if (!isSameOrLowerThanTop(prevOp, op)) {
				break;
			}
		}

		if (prevOp == '(' && op == ')') {
			pop(s);

			break;
		}

		if (prevOp == '(') {
			break;
		}

		if (op != '(') {
			printf("%c", pop(s));
		}
	}
}

Boolean isSameOrLowerThanTop(char prevOp, char op) {
	return (getOperatorPrecedence(prevOp) >= getOperatorPrecedence(op));
}

int getOperatorPrecedence(char op) {
	switch (op) {
		case '(':
		case ')':
			return 3;
		case '*':
		case '/':
		case '%':
			return 2;
		case '+':
		case '-':
			return 1;
	}
}