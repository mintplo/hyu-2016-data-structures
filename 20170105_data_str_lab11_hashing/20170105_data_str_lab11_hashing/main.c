#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct ListNode* Position;
typedef Position List;
typedef struct hashTable* HashTable;
struct ListNode {
	ElementType element;
	Position next;
};
struct hashTable {
	int tableSize;
	List* lists;
};

HashTable createHashTable(int size);
int hash(ElementType value, int size);
void insert(ElementType key, HashTable h);
int find(HashTable h, ElementType value);

void main(int argc, char** argv) {
	FILE* fp;
	HashTable h;
	int value;

	h = createHashTable(30);
	insert(3, h);
	insert(5, h);
	insert(35, h);
	insert(2, h);
	insert(7, h);
	insert(18, h);
	insert(19, h);
	insert(22, h);
	insert(5, h);
	insert(100, h);
	insert(26, h);
	insert(8, h);
	insert(4, h);
	insert(16, h);

	if (find(h, 5) == 5) {
		printf("get 5\n");
	}

	if (find(h, 27) == 27) {
		printf("get 27\n");
	}

	if (find(h, 45) == 45) {
		printf("get 45\n");
	}
	if (find(h, 67) == 67) {
		printf("get 67\n");
	}
	if (find(h, 2) == 2) {
		printf("get 2\n");
	}
}

HashTable createHashTable(int size) {
	int i;
	HashTable h = (HashTable)malloc(sizeof(struct hashTable));
	if (!h) {
		exit(EXIT_FAILURE);
	}

	h->lists = (List*)calloc(size, sizeof(Position));
	if (!h->lists) {
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < size; i++) {
		h->lists[i] = (Position)malloc(sizeof(struct ListNode));
		h->lists[i]->element = 0;
		h->lists[i]->next = NULL;
	}

	h->tableSize = size;

	return h;
}

int hash(ElementType value, int size) {
	return (((27 * value + value) * 27) + value) % size;
}

void insert(ElementType key, HashTable h) {
	Position p = NULL, n;
	if (!h) {
		return;
	}

	n = find(h, key);
	if (n == NULL) {
		return;
	}

	n = (Position)malloc(sizeof(struct ListNode));
	n->element = key;

	p = h->lists[hash(key, h->tableSize)];
	n->next = p->next;
	p->next = n;
}

int find(HashTable h, ElementType value) {
	if (!h) {
		return -1;
	}

	Position p = h->lists[hash(value, h->tableSize)];
	while (p != NULL && p->element != value)
		p = p->next;

	if (!p) {
		return -1;
	}

	return p->element;
}
