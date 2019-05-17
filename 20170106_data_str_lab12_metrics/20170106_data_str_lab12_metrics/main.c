#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct QueueStruct* Queue;
struct QueueStruct {
	int size;
	int capacity;
	int front;
	int rear;
	ElementType* elements;
};

Queue createQueue(int size);
int isQueueFull(Queue q);
int isQueueEmpty(Queue q);
void enqueue(Queue q, ElementType element);
ElementType dequeue(Queue q);

ElementType** createMetrics(int rows, int cols);
void topologySort(ElementType** graphs, ElementType* vertex, int vertexSize);
ElementType* checkIndegrees(ElementType** graphs, int vertexSize);

void main(int argc, char** argv) {
	int i = 0;
	ElementType** graphs = NULL;
	ElementType* vertex = NULL;

	vertex = (ElementType*)calloc(6, sizeof(ElementType));
	for (i = 0; i < 6; i++) {
		vertex[i] = i + 1;
	}

	graphs = createMetrics(6, 6);
	graphs[0][1] = 1;
	graphs[0][3] = 1;
	graphs[1][4] = 1;
	graphs[1][3] = 1;
	graphs[1][2] = 1;
	graphs[2][3] = 1;
	graphs[4][2] = 1;
	graphs[5][2] = 1;
	graphs[5][4] = 1;

	topologySort(graphs, vertex, 6);
}

Queue createQueue(int size) {
	Queue temp = (Queue)malloc(sizeof(struct QueueStruct));
	if (!temp) {
		exit(EXIT_FAILURE);
	}

	temp->elements = (ElementType*)calloc(size, sizeof(ElementType));
	if (!temp->elements) {
		exit(EXIT_FAILURE);
	}

	temp->size = 0;
	temp->capacity = size;
	temp->front = 0;
	temp->rear = -1;
}

int isQueueFull(Queue q) {
	return (q != NULL && q->size >= q->capacity);
}

int isQueueEmpty(Queue q) {
	return (q != NULL && q->size == 0);
}

void enqueue(Queue q, ElementType element) {
	if (isQueueFull(q)) {
		return;
	}

	q->size++;
	q->rear = (q->rear + 1) % q->capacity;
	q->elements[q->rear] = element;
}

ElementType dequeue(Queue q) {
	ElementType temp;

	if (isQueueEmpty(q)) {
		return -1;
	}

	temp = q->elements[q->front];
	q->size--;
	q->front = (q->front + 1) % q->capacity;

	return temp;
}

ElementType** createMetrics(int rows, int cols) {
	int i;

	ElementType** metrics = (ElementType*)calloc(rows, sizeof(ElementType*));
	if (!metrics) {
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < rows; i++) {
		metrics[i] = (ElementType)calloc(cols, sizeof(ElementType));

		if (!metrics[i]) {
			exit(EXIT_FAILURE);
		}
	}

	return metrics;
}

void topologySort(ElementType** graphs, ElementType* vertex, int vertexSize) {
	int i;
	Queue q = NULL;
	ElementType temp;
	ElementType* indegrees = NULL;

	q = createQueue(100);
	indegrees = checkIndegrees(graphs, vertexSize);

	for (i = 0; i < vertexSize; i++) {
		if (indegrees[i] == 0) {
			enqueue(q, i);
		}
	}

	while (!isQueueEmpty(q)) {
		temp = dequeue(q);

		for (i = 0; i < vertexSize; i++) {
			if (graphs[temp][i] == 1) {
				if (--indegrees[i] == 0) {
					enqueue(q, i);
				}
			}
		}

		printf("%3d", vertex[temp]);
	}
}

ElementType* checkIndegrees(ElementType** graphs, int vertexSize) {
	int i, j;
	ElementType* indegrees = (ElementType*)calloc(vertexSize, sizeof(ElementType));

	for (i = 0; i < vertexSize; i++) {
		for (j = 0; j < vertexSize; j++) {
			if (graphs[j][i] == 1) {
				indegrees[i]++;
			}
		}
	}

	return indegrees;
}