#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void perm(char*, int, int);
void swap(char*, char*);
void main_(void) {
	char list[] = { 'a', 'b', 'c' };

	perm(list, 0, 3);
}

void swap(char* x, char* y) {
	char temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

void perm(char* list, int i, int n) {
	int j, temp;
	if (i == n) {
		for (j = 0; j < n; j++)
			printf("%c", list[j]);
		printf("\n");
	}
	else {
		for (j = i; j < n; j++) {
			swap(&list[i], &list[j]);
			perm(list, i + 1, n);
			swap(&list[i], &list[j]);
		}
	}
}
