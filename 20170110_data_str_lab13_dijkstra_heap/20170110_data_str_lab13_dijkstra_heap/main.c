// Graph - Array
// Heap - Array
#include <stdio.h>
#include <stdlib.h>

typedef int* Vertex;
typedef int** Graph;
typedef struct NodeStruct* Node;
typedef struct HeapStruct* Heap;
struct NodeStruct {
	int vertex;
	int priority;
};
struct HeapStruct {
	int capacity;
	int size;
	Node* elements;
};

Graph createGraph(int graphSize);
Vertex createVertex(int graphSize);
void insertVertex(Vertex v, int vertex, int graphSize);
void insertEdge(Graph g, int from, int to, int priority);

int findHeap(Heap h, int vertex);
void insertHeap(Heap h, int vertex, int priority);
void updateHeap(Heap h, int vertex, int priority);
Node deleteMin(Heap h);

void dijikstra(Heap h, Graph g, Vertex v, int graphSize, int source);

void main(int argc, char** argv) {
	Graph g = NULL;
	Vertex v = NULL;
	Heap h = (Heap)malloc(sizeof(struct HeapStruct));
	if (!h) {
		exit(EXIT_FAILURE);
	}

	h->elements = (Node*)calloc(10, sizeof(struct NodeStruct));
	if (!h->elements) {
		exit(EXIT_FAILURE);
	}

	h->size = 0;
	h->capacity = 10;

	g = createGraph(7);
	v = createVertex(7);

	insertVertex(v, 1, 7);
	insertVertex(v, 2, 7);
	insertVertex(v, 3, 7);
	insertVertex(v, 4, 7);
	insertVertex(v, 5, 7);
	insertVertex(v, 6, 7);
	insertVertex(v, 7, 7);

	insertEdge(g, 0, 1, 2);
	insertEdge(g, 0, 3, 1);
	insertEdge(g, 1, 4, 10);
	insertEdge(g, 1, 3, 3);
	insertEdge(g, 2, 0, 4);
	insertEdge(g, 2, 5, 5);
	insertEdge(g, 3, 5, 8);
	insertEdge(g, 4, 6, 4);
	insertEdge(g, 3, 4, 2);
	insertEdge(g, 4, 6, 6);
	insertEdge(g, 6, 5, 1);

	dijikstra(h, g, v, 7, 2);
}

Graph createGraph(int graphSize) {
	int **temp = NULL, i;

	temp = (int**)calloc(graphSize, sizeof(int));
	if (!temp) {
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < graphSize; i++) {
		temp[i] = (int*)malloc(sizeof(int));

		if (!temp[i]) {
			exit(EXIT_FAILURE);
		}
	}

	return temp;
}

Vertex createVertex(int graphSize) {
	int *temp = NULL;

	temp = (int*)calloc(graphSize, sizeof(int));
	if (!temp) {
		exit(EXIT_FAILURE);
	}

	return temp;
}

void insertVertex(Vertex v, int vertex, int graphSize) {
	int i;

	for (i = 0; i < graphSize; i++) {
		if (v[i] == 0) {
			continue;
		}

		v[i] = vertex;
		return;
	}
}

void insertEdge(Graph g, int from, int to, int priority) {
	g[from][to] = priority;
}

int findHeap(Heap h, int vertex) {
	int i;

	for (i = 1; i <= h->size; i++) {
		if (h->elements[i]->vertex == vertex) {
			return i;
		}
	}
}

void insertHeap(Heap h, int vertex, int priority) {
	int i;
	Node temp = (Node)malloc(sizeof(struct NodeStruct));
	if (!temp) {
		return;
	}

	temp->vertex = vertex;
	temp->priority = priority;

	for (i = ++h->size; h->elements[i / 2] && (h->elements[i / 2]->priority < priority); i /= 2)
		h->elements[i] = h->elements[i / 2];

	h->elements[i] = temp;
}

void updateHeap(Heap h, int vertex, int priority) {
	int i, j;
	Node u = NULL;

	i = findHeap(h, vertex);
	u = h->elements[i];
	u->priority = priority;

	for (j = i; h->elements[i / 2] && (h->elements[i / 2]->priority > priority); i /= 2)
		h->elements[i] = h->elements[i / 2];

	h->elements[i] = u;
}

Node deleteMin(Heap h) {
	int i, child;
	Node lastElement, minElement;

	minElement = h->elements[1];
	lastElement = h->elements[h->size--];

	for (i = 1; i * 2 <= h->size; i = child) {
		child = i * 2;

		if (child != h->size && h->elements[child]->priority > h->elements[child + 1]->priority)
			child++;

		if (h->elements[child]->priority < lastElement->priority)
			h->elements[i] = h->elements[child];
		else
			break;
	}

	h->elements[i] = lastElement;

	return minElement;
}

void dijikstra(Heap h, Graph g, Vertex v, int graphSize, int source) {
	int i, temp, spOffset = 0;
	Node u = NULL;
	int* result = (int*)calloc(graphSize, sizeof(int));
	int* distance = (int*)calloc(graphSize, sizeof(int));
	int* pred = (int*)calloc(graphSize, sizeof(int));

	for (i = 0; i < graphSize; i++) {
		distance[i] = 10000;
		pred[i] = 0;
	}
	distance[source] = 0;

	for (i = 0; i < graphSize; i++) {
		if (g[source][i] > 0) {
			distance[i] = g[source][i] + distance[source];
			pred[i] = source;
		}
	}

	for (i = 0; i < graphSize; i++) {
		if (i == source)
			continue;

		insertHeap(h, i, distance[i]);
	}

	result[spOffset++] = source;

	while (h->size > 0) {
		u = deleteMin(h);

		result[spOffset++] = u->vertex;
		temp = findHeap(h, u->vertex);
		for (i = 0; i < graphSize; i++) {
			if (g[temp][i] > 0) {
				if (g[temp][i] + distance[temp] < distance[i]) {
					distance[i] = g[temp][i] + distance[temp];
					pred[i] = temp;
					updateHeap(h, temp, distance[temp]);
				}
			}
		}
	}

	for (i = 0; i < graphSize; i++)
		printf("%3d", result[i]);
}