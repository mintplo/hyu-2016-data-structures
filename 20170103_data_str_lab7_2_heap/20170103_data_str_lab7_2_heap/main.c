#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct heapStruct HeapStruct;
struct heapStruct {
	int capacity;
	int size;
	ElementType *elements;
};

HeapStruct* createHeap(int heapSize);
void insert(HeapStruct* heap, ElementType element);
ElementType deleteMax(HeapStruct* heap);
void printHeap(HeapStruct* heap);

void main(int argc, char** argv) {
	char cmd;
	int cmdOffset;
	FILE* fp;
	HeapStruct* heap = NULL;

	fp = fopen(argv[1], "r");
	if (!fp) {
		fprintf(stderr, "File Input Error!\n");

		exit(EXIT_FAILURE);
	}

	while (!feof(fp)) {
		cmd = fgetc(fp);

		switch (cmd) {
			case 'n':
				fscanf(fp, "%d\n", &cmdOffset);
				heap = createHeap(cmdOffset);
				break;
			case 'i':
				fscanf(fp, "%d\n", &cmdOffset);
				insert(heap, cmdOffset);
				break;
			case 'd':
				fgetc(fp); // remove \n
				deleteMax(heap);
				break;
			case 'p':
				fgetc(fp); // remove \n
				printHeap(heap);
				break;
			default:
				break;
		}
	}
}

HeapStruct* createHeap(int heapSize) {
	HeapStruct* heap = (HeapStruct *)malloc(sizeof(struct heapStruct));
	if (!heap) {
		fprintf(stderr, "Create Heap Failed: out of memory\n");

		exit(EXIT_FAILURE);
	}

	heap->elements = (ElementType *)calloc(heapSize, sizeof(ElementType));
	if (!heap->elements) {
		fprintf(stderr, "Create Heap Failed: out of memory\n");

		exit(EXIT_FAILURE);
	}

	heap->capacity = heapSize;
	heap->size = 0;

	return heap;
}

void insert(HeapStruct* heap, ElementType element) {
	int i;

	if (heap->size >= heap->capacity) {
		fprintf(stderr, "Insert Heap Failed: heap is full\n");

		return;
	}

	for (i = ++heap->size; heap->elements[i / 2] && (heap->elements[i / 2] < element); i /= 2)
		heap->elements[i] = heap->elements[i / 2];

	heap->elements[i] = element;
}

ElementType deleteMax(HeapStruct* heap) {
	int i, child;
	ElementType maxElement, lastElement;

	if (heap->size <= 0) {
		fprintf(stderr, "Heap Max Deletion Failed: Heap is empty!\n");

		return -1;
	}

	maxElement = heap->elements[1];
	lastElement = heap->elements[heap->size--];

	for (i = 1; i * 2 <= heap->size; i = child) {
		child = i * 2;
		if (child != heap->size && heap->elements[child] < heap->elements[child + 1]) {
			child++;
		}

		if (lastElement > heap->elements[child])
			break;

		heap->elements[i] = heap->elements[child];
	}

	heap->elements[i] = lastElement;

	return maxElement;
}

void printHeap(HeapStruct* heap) {
	int i;

	if (!heap) {
		fprintf(stderr, "Print Heap Failed: Heap is null!\n");

		exit(EXIT_FAILURE);
	}

	printf("Print Heap Start ======\n");
	for (i = 1; i <= heap->size; i++) {
		printf("%d\n", heap->elements[i]);
	}
	printf("Print Heap End ======\n");

	return;
}