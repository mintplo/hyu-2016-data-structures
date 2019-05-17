#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef enum { TRUE = 1, FALSE = 0} Boolean;
typedef struct Node* PtrToNode;
typedef PtrToNode Stack;
struct Node {
	int Element;
	PtrToNode Next;
};

Stack createStack(Stack s);
Boolean isEmpty(Stack s);
char pop(Stack s);
void push(Stack s, int value);
void printStack(Stack s);

Boolean isNumeric(char element);

void main(int argc, char** argv) {
	FILE* fr = NULL;
	Stack s = NULL;
	char ch;
	int operand1, operand2, result;

	fr = fopen(argv[1], "r");
	s = createStack(s);

	while ((ch = fgetc(fr)) != '#') {
		if (isNumeric(ch)) {
			push(s, atoi(&ch));
			printStack(s);

			continue;
		}

		operand2 = pop(s);
		operand1 = pop(s);

		switch (ch) {
			case '+':
				result = operand1 + operand2;
				break;
			case '-':
				result = operand1 - operand2;
				break;
			case '*':
				result = operand1 * operand2;
				break;
			case '/':
				result = operand1 / operand2;
				break;
			case '%':
				result = operand1 % operand2;
				break;
			default:
				break;
		}

		push(s, result);

		printStack(s);
	}

	printf("Result: %d", s->Next->Element);
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

void push(Stack s, int e) {
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
			return 0;
		default:
			return 1;
	}
}