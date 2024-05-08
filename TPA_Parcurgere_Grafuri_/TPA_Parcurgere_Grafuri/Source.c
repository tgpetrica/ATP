#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct Nod 
{
	int varf;
	struct Nod* copil;
} Nod;

typedef struct Queue
{
	int value;
	struct Queue* y;
} Queue;

void adaugaMuchie	(Nod** listaAdiacenta, int nod1, int nod2);
void citire			(int noduri, Nod** listaAdiacenta);
void afisare		(int noduri, Nod** listaAdiacenta);
void dealocare		(int noduri, Nod** listaAdiacenta);

//stack
void push			(int* stack, int* top, int x);
int pop				(int* stack, int* top);

//queue
void pushBack		(Queue** L, Queue** R, int x);
int popBack			(Queue** L, Queue** R);

// parcurgeri
// Breadth-First
void BFS			(int start, int noduri, Nod** listaAdiacenta);
// Depth-First
void DFS			(int start, int noduri, Nod** listaAdiacenta);

void main()
{
	int noduri;
	printf("Introdu numarul de noduri: ");
	scanf("%d", &noduri);

	Nod** listaAdiacenta = (Nod**)malloc((noduri + 1) * sizeof(Nod*));

	for (int i = 0; i <= noduri; i++)
	{
		listaAdiacenta[i] = NULL;
	}

	citire(noduri, listaAdiacenta);
	
	printf("Lista de adiacenta:\n");
	afisare(noduri, listaAdiacenta);

	int start;
	printf("Introdu nodul de start: ");
	scanf("%d", &start);

	DFS(start, noduri, listaAdiacenta);
	printf("\n\n");
	BFS(start, noduri, listaAdiacenta);

	dealocare(noduri, listaAdiacenta);
}

void adaugaMuchie(Nod** listaAdiacenta, int nod1, int nod2)
{
	Nod* nod = (Nod*)malloc(sizeof(Nod));
	nod->varf = nod2;
	nod->copil = listaAdiacenta[nod1];
	listaAdiacenta[nod1] = nod;
}

void citire(int noduri, Nod** listaAdiacenta)
{
	int nod;
	printf("Pentru fiecare nod, citirea muchiilor se face introducand numarul\
varfurilor catre care pleaca o muchie de la nodul curent.\n \
Introducerea numarului nodului curent incheie citirea pentru \
respectivul nod.\n");
	for (int i = 1; i <= noduri; i++)
	{
		printf("De la nodul \n%d exista muchii catre: ", i);
		while (1)
		{
			scanf("\t%d", &nod);
			if (nod == i)
			{
				break;
			}
			else {
				adaugaMuchie(listaAdiacenta, i, nod);
			}
		}
	}
}

void afisare(int noduri, Nod** listaAdiacenta)
{
	for (int i = 1; i <= noduri; i++)
	{
		printf("Nodul %d: ", i);
		Nod* curent = listaAdiacenta[i];
		while (curent != NULL)
		{
			printf("%d, ", curent->varf);
			curent = curent->copil;
		}
		printf("\n");
	}
}

void dealocare(int noduri, Nod** listaAdiacenta)
{
	for (int i = 1; i <= noduri; i++)
	{
		Nod* curent = listaAdiacenta[i];
		while (curent != NULL)
		{
			Nod* temp = curent;
			curent = curent->copil;
			free(temp);
		}
	}
	free(listaAdiacenta);
}

void push(int* stack, int* top, int x)
{
	stack[++(*top)] = x;
}

int pop(int* stack, int* top)
{
	if (*top == -1)
	{
		return -1;
	}
	return stack[(*top)--];
}

void pushBack(Queue** L, Queue** R, int x)
{
	Queue* nod = (Queue*)malloc(sizeof(Queue));

	if (nod == NULL)
	{
		printf("Eroare la alocarea memoriei.");
		return;
	}

	nod->value = x;
	nod->y = NULL;

	if (*R == NULL)
	{
		*L = *R = nod;
	}
	else {
		(*R)->y = nod;
		*R = nod;
	}
}

int popBack(Queue** L, Queue** R)
{
	if (*L == NULL)
	{
		return -1;
	}

	Queue* temp = *L;
	int x = temp->value;
	*L = (*L)->y;

	if (*L == NULL)
	{
		*R = NULL;
	}

	free(temp);
	return x;
}

void BFS(int start, int noduri, Nod** listaAdiacenta)
{
	int* visited = (int*)malloc((noduri + 1) * sizeof(int));

	if (visited == NULL)
	{
		printf("Eroare la alocarea memoriei.");
		return;
	}

	for (int i = 0; i <= noduri; i++)
	{
		visited[i] = 0;
	}

	Queue* L = NULL, * R = NULL;

	visited[start] = 1;
	pushBack(&L, &R, start);

	printf("BFS: \n====\n");

	while (L != NULL)
	{
		int curr = popBack(&L, &R);
		printf("%d ", curr);

		Nod* temp = listaAdiacenta[curr];
		while (temp != NULL)
		{
			int adiacent = temp->varf;
			if (visited[adiacent] == 0)
			{
				visited[adiacent] = 1;
				pushBack(&L, &R, adiacent);
			}
			temp = temp->copil;
		}
	}
	printf("\n");

	free(visited);
}

void DFS(int start, int noduri, Nod** listaAdiacenta)
{
	int* visited = (int*)malloc((noduri + 1) * sizeof(int));
	if (visited == NULL)
	{
		printf("Eroare la alocarea memoriei.\n");
		return;
	}

	for (int i = 0; i <= noduri; i++)
	{
		visited[i] = 0;
	}

	int* stack = (int*)malloc((noduri + 1) * sizeof(int));
	int top = -1;

	visited[start] = 1;
	push(stack, &top, start);

	printf("DFS: \n====\n");

	while (top != -1)
	{
		int curr = pop(stack, &top);
		printf("%d ", curr);

		Nod* temp = listaAdiacenta[curr];
		while (temp != NULL)
		{
			int adiacent = temp->varf;
			if (visited[adiacent] == 0)
			{
				visited[adiacent] = 1;
				push(stack, &top, adiacent);
			}
			temp = temp->copil;
		}
	}
	printf("\n");

	free(visited);
	free(stack);
}

/*
* 
* Exemplu rulare:
* Introdu numarul de noduri: 13
Pentru fiecare nod, citirea muchiilor se face introducand numarulvarfurilor catre care pleaca o muchie de la nodul curent.
 Introducerea numarului nodului curent incheie citirea pentru respectivul nod.
De la nodul
1 exista muchii catre: 2
3
4
1
De la nodul
2 exista muchii catre: 5
6
2
De la nodul
3 exista muchii catre: 3
De la nodul
4 exista muchii catre: 7
8
4
De la nodul
5 exista muchii catre: 9
10
5
De la nodul
6 exista muchii catre: 6
De la nodul
7 exista muchii catre: 12
7
De la nodul
8 exista muchii catre: 8
De la nodul
9 exista muchii catre: 11
9
De la nodul
10 exista muchii catre: 10
De la nodul
11 exista muchii catre: 11
De la nodul
12 exista muchii catre: 13
12
De la nodul
13 exista muchii catre: 13
Lista de adiacenta:
Nodul 1: 4, 3, 2,
Nodul 2: 6, 5,
Nodul 3:
Nodul 4: 8, 7,
Nodul 5: 10, 9,
Nodul 6:
Nodul 7: 12,
Nodul 8:
Nodul 9: 11,
Nodul 10:
Nodul 11:
Nodul 12: 13,
Nodul 13:
Introdu nodul de start: 1
DFS:
====
1 2 5 9 11 10 6 3 4 7 12 13 8


BFS:
====
1 4 3 2 8 7 6 5 12 10 9 13 11
*/