#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct CircularQueue* Queue;
struct CircularQueue {
	int front;
	int rear;
	int qSize;
	int maxSize;
	ElementType* elements;
};

Queue makeEmpty(int maxSize);
int isEmpty(Queue q);
int isFull(Queue q);
void dequeue(Queue q);
void enqueue(Queue q, ElementType e);
void printFront(Queue q);
void printRear(Queue q);
void deleteQueue(Queue q);

void main(int argc, char** argv) {
	FILE *fr = NULL;
	Queue q = NULL;
	char cmd;
	int temp;

	fr = fopen(argv[1], "r");

	while (!feof(fr)) {
		cmd = fgetc(fr);

		switch (cmd) {
		case 'n':
			fscanf(fr, "%d\n", &temp);
			q = makeEmpty(temp);
			break;
		case 'e':
			fscanf(fr, "%d\n", &temp);
			enqueue(q, temp);
			break;
		case 'd':
			dequeue(q);
			fgetc(fr);
			break;
		case 'f':
			printFront(q);
			fgetc(fr);
			break;
		case 'r':
			printRear(q);
			fgetc(fr);
			break;
		default:
			break;
		}
	}
}

Queue makeEmpty(int maxSize) {
	Queue q = (Queue)malloc(sizeof(struct CircularQueue));
	q->elements = (ElementType *)malloc(sizeof(ElementType) * maxSize);

	if (q == NULL || q->elements == NULL) {
		fprintf(stderr, "Queue Make Failed: Out of Memory\n");

		exit(EXIT_FAILURE);
	}

	q->front = 0;
	q->rear = -1;
	q->qSize = 0;
	q->maxSize = maxSize;

	return q;
}

int isEmpty(Queue q) {
	return q->qSize == 0;
}

int isFull(Queue q) {
	return q->qSize == q->maxSize;
}

void dequeue(Queue q) {
	if (isEmpty(q)) {
		fprintf(stderr, "Dequeue Failed: Queue is empty\n");

		return;
	}

	q->qSize--;
	q->front = (q->front + 1) % q->maxSize;
}

void enqueue(Queue q, ElementType e) {
	if (isFull(q)) {
		fprintf(stderr, "Enqueue Failed: Queue is full\n");

		return;
	}

	q->qSize++;
	q->rear = (q->rear + 1) % q->maxSize;
	q->elements[q->rear] = e;
}

void printFront(Queue q) {
	if (isEmpty(q)) {
		fprintf(stderr, "Print Failed: Queue is empty\n");

		return;
	}

	printf("Front: %d\n", q->elements[q->front]);
}

void printRear(Queue q) {
	if (isEmpty(q)) {
		fprintf(stderr, "Print Failed: Queue is empty\n");

		return;
	}

	printf("Rear: %d\n", q->elements[q->rear]);
}

void deleteQueue(Queue q) {
	free(q->elements);
	free(q);
}
