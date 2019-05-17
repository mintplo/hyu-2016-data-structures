#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE 101
#define SWAP(x, y, t) \
	( (t) = (x), (x) = (y), (y) = (t) )

void sort(int[], int size);
void main(void) {
	int i, n;
	int list[MAX_SIZE];

	printf("Enter the number of numbers to generate: ");
	scanf("%d", &n);

	if (n < 1 || n > MAX_SIZE) {
		// �⺻������ ���� ����������� stderr�� stdin, stdout�� �����Ϳ� ����ϴ� ��.
		fprintf(stderr, "Improper Value of n\n");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < n; i++) {
		list[i] = rand() % 1000;
		printf("%d	", list[i]);

		if (i % 10 == 0) {
			printf("\n");
		}
	}

	sort(list, n);
	printf("\n Sorted array:\n");

	for (i = 0; i < n; i++) {
		printf("%d	", list[i]);
	}
}

void sort(int list[], int size) {
	int i, j, min, temp;

	for (i = 0; i < size - 1; i++) {
		min = i;
		for (j = i + 1; j < size; j++) {
			if (list[min] > list[j]) {
				min = j;
			}
		}

		SWAP(list[i], list[min], temp);
	}
}