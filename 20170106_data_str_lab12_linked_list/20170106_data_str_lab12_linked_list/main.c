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

typedef struct GraphStruct* Graphs;
typedef struct VertexStruct* Edge;
typedef struct VertexStruct* Vertex;
struct VertexStruct {
	ElementType title;
	Edge next;
};
struct GraphStruct {
	Vertex* vertexes;
	int vertexSize;
};

Queue createQueue(int size);
int isQueueFull(Queue q);
int isQueueEmpty(Queue q);
void enqueue(Queue q, ElementType element);
ElementType dequeue(Queue q);

Graphs createGraphs(int vertexSize);
void addVertexToGraphs(Graphs g, int vertex);
void addEdgeToGraphs(Graphs g, int from, int to);
int findVertexPosWithTitle(Graphs g, ElementType title);

void topologySort(Graphs g);
int* checkIndegrees(Graphs g);

void main(int argc, char** argv) {
	Graphs g = NULL;

	g = createGraphs(6);

	addVertexToGraphs(g, 1);
	addVertexToGraphs(g, 2);
	addVertexToGraphs(g, 3);
	addVertexToGraphs(g, 4);
	addVertexToGraphs(g, 5);
	addVertexToGraphs(g, 6);

	addEdgeToGraphs(g, 1, 2);
	addEdgeToGraphs(g, 1, 4);
	addEdgeToGraphs(g, 2, 5);
	addEdgeToGraphs(g, 2, 4);
	addEdgeToGraphs(g, 2, 3);
	addEdgeToGraphs(g, 3, 4);
	addEdgeToGraphs(g, 5, 3);
	addEdgeToGraphs(g, 6, 3);
	addEdgeToGraphs(g, 6, 5);

	topologySort(g);
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

void topologySort(Graphs g) {
	int i, pos;
	int* ind = NULL;
	Queue q = NULL;
	ElementType temp;
	Edge p;

	q = createQueue(100);
	ind = checkIndegrees(g);

	for (i = 0; i < g->vertexSize; i++) {
		if (ind[i] == 0) {
			enqueue(q, i);
		}
	}

	while (!isQueueEmpty(q)) {
		temp = dequeue(q);

		p = g->vertexes[temp]->next;
		while (p != NULL) {
			pos = findVertexPosWithTitle(g, p->title);
			if (--ind[pos] == 0) {
				enqueue(q, pos);
			}

			p = p->next;
		}

		printf("%3d", g->vertexes[temp]->title);
	}
}

int* checkIndegrees(Graphs g) {
	int i;
	Edge p;
	int* indegrees = (int*)calloc(g->vertexSize, sizeof(int));
	if (!indegrees) {
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < g->vertexSize; i++) {
		indegrees[i] = 0;
	}

	for (i = 0; i < g->vertexSize; i++) {
		p = g->vertexes[i]->next;

		while (p != NULL) {
			++indegrees[findVertexPosWithTitle(g, p->title)];
			p = p->next;
		}
	}

	return indegrees;
}

Graphs createGraphs(int vertexSize) {
	int i;
	Graphs g = (Graphs)calloc(vertexSize, sizeof(struct GraphStruct));
	if (!g) {
		exit(EXIT_FAILURE);
	}

	g->vertexSize = vertexSize;
	g->vertexes = (Vertex*)calloc(g->vertexSize, sizeof(Vertex));

	return g;
}

void addVertexToGraphs(Graphs g, int vertex) {
	int i = 0;
	while (i <= g->vertexSize && g->vertexes[i] != NULL)
		i++;

	g->vertexes[i] = (Vertex)malloc(sizeof(struct VertexStruct));
	g->vertexes[i]->title = vertex;
	g->vertexes[i]->next = NULL;
}

void addEdgeToGraphs(Graphs g, int from, int to) {
	Edge temp;
	int i = 0;
	while (i <= g->vertexSize && g->vertexes[i]->title != from)
		i++;

	temp = (Edge)malloc(sizeof(struct VertexStruct));
	if (!temp) {
		exit(EXIT_FAILURE);
	}

	temp->title = to;
	temp->next = g->vertexes[i]->next;
	g->vertexes[i]->next = temp;
}

int findVertexPosWithTitle(Graphs g, ElementType title) {
	int i;

	for (i = 0; i < g->vertexSize; i++) {
		if (g->vertexes[i]->title == title) {
			return i;
		}
	}
}