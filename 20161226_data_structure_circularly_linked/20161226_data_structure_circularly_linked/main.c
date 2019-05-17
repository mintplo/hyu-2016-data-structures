#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef enum { FALSE = 0, TRUE = 1 } Boolean;

typedef int ElementType;
typedef struct Node* PtrNode;
typedef PtrNode Position;
typedef PtrNode List;
struct Node {
	ElementType element;
	Position prev;
	Position next;
};

List makeEmpty(List l);
Boolean isEmpty(List l);
Position find(ElementType x, List l);
void delete(ElementType x, List l);
void insert(ElementType x, List l, ElementType y);
void deleteList(List l);
void printList(List l);

void main(int argc, char** argv) {
	char cmd;
	int element, pos;
	FILE *fp;
	Position p;
	List l = NULL; // 포인터는 초기화하지 않은 채 사용하면 오류 (초기화 하지 않은 채 함수 리턴 값 대입하면 안되는 듯)
	l = makeEmpty(l);

	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		fprintf(stderr, "File Not Open Error");
	}

	while (!feof(fp)) {
		cmd = NULL;
		fscanf(fp, "%c", &cmd);

		switch (cmd) {
		case 'i':
			fscanf(fp, "%d %d\n", &element, &pos);
			insert(element, l, pos);
			break;
		case 'd':
			fscanf(fp, "%d\n", &element);
			delete(element, l);
			break;
		case 'f':
			fscanf(fp, "%d\n", &element);

			p = find(element, l);
			if (p == NULL) {
				printf("\nCould Not Find (%d) in the list.", element);
			}

			break;
		case 'p':
			printList(l);
			break;
		case 'a':
			deleteList(l);
			break;
		default:
			break;
		}
	}

	fclose(fp);
}

List makeEmpty(List l) {
	l = (List)malloc(sizeof(struct Node));
	if (l == NULL) {
		fprintf(stderr, "Out Of Memory");
		exit(EXIT_FAILURE);
	}

	l->element = 0;
	l->next = l;
	l->prev = l;

	return l;
}

Boolean isEmpty(List l) {
	return l->next == l && l->prev == l;
}

Position find(ElementType x, List l) {
	Position p = l->next;

	// 요소를 찾는 조건 주의!
	while (p != l && p->element != x)
		p = p->next;

	return p;
}

void delete(ElementType x, List l) {
	Position p, tmp;

	p = find(x, l);
	if (p == l) {
		fprintf(stderr, "Deletion Failed: element(%d) is not in the list\n", x, x);
		return;
	}

	tmp = p;
	p->next->prev = p->prev;
	p->prev->next = p->next;
	free(tmp); // p deallocation returing heap memory for space which allocating dynamically
}

void insert(ElementType x, List l, ElementType y) {
	Position target;
	Position temp = (Position)malloc(sizeof(struct Node));
	if (temp == NULL) {
		fprintf(stderr, "Out of Memory");
		exit(EXIT_FAILURE);
	}

	if (y == -1) { // 헤더 바로 뒤에 삽입
		target = l;
	}
	else { // 요소 찾아서 삽입
		target = find(y, l);
		if (target == l) {
			fprintf(stderr, "Insertion(%d) Failed: element(%d) is not in the list\n", x, y);
			return;
		}
	}

	temp->element = x;
	temp->next = target->next;
	temp->prev = target;
	temp->next->prev = temp;
	target->next = temp;
}

void deleteList(List l) {
	Position tmp, p;

	p = l->next;
	while (p != l) {
		tmp = p->next;
		free(p);
		p = tmp;
	}

	l->next = l;
	l->prev = l;
}

void printList(List l) {
	Position p;
	p = l->next;

	printf("\n == List  Print == \n");
	while (p != l) {
		printf("Key : %d\n", p->element);
		p = p->next;
	}
}