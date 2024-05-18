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

void adaugaMuchie(Nod** listaAdiacenta, int nod1, int nod2);
void citireFisier(int noduri, int muchii, Nod** listaAdiacenta, FILE* fisier);
void afisare(int noduri, Nod** listaAdiacenta);
void dealocare(int noduri, Nod** listaAdiacenta);

// stack
void push(int* stack, int* top, int x);
int pop(int* stack, int* top);

// queue
void pushBack(Queue** L, Queue** R, int x);
int popBack(Queue** L, Queue** R);

// parcurgeri
// Breadth-First
void BFS(int start, int noduri, Nod** listaAdiacenta);
// Depth-First
void DFS(int start, int noduri, Nod** listaAdiacenta);

void main() 
{
    int noduri, muchii;
    char* numeFisier = "input.txt";

    FILE* fisier = fopen(numeFisier, "r");
    if (fisier == NULL) 
    {
        printf("Eroare la deschiderea fisierului.\n");
        return 1;
    }

    fscanf(fisier, "%d %d", &noduri, &muchii);

    Nod** listaAdiacenta = (Nod**)malloc((noduri + 1) * sizeof(Nod*));
    for (int i = 0; i <= noduri; i++) 
    {
        listaAdiacenta[i] = NULL;
    }

    citireFisier(noduri, muchii, listaAdiacenta, fisier);

    printf("Lista de adiacenta:\n");
    afisare(noduri, listaAdiacenta);

    int start;
    printf("Introdu nodul de start: ");
    scanf("%d", &start);

    DFS(start, noduri, listaAdiacenta);
    printf("\n\n");
    BFS(start, noduri, listaAdiacenta);

    dealocare(noduri, listaAdiacenta);

    fclose(fisier);
}

void adaugaMuchie(Nod** listaAdiacenta, int nod1, int nod2) 
{
    Nod* nod = (Nod*)malloc(sizeof(Nod));
    nod->varf = nod2;
    nod->copil = listaAdiacenta[nod1];
    listaAdiacenta[nod1] = nod;
}

void citireFisier(int noduri, int muchii, Nod** listaAdiacenta, FILE* fisier) 
{
    int nod1, nod2;

    for (int i = 0; i < muchii; i++) 
    {
        fscanf(fisier, "%d %d", &nod1, &nod2);
        adaugaMuchie(listaAdiacenta, nod1, nod2);
        adaugaMuchie(listaAdiacenta, nod2, nod1);
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
        printf("Eroare la alocarea memoriei.\n");
        return;
    }

    nod->value = x;
    nod->y = NULL;

    if (*R == NULL) 
    {
        *L = *R = nod;
    } else {
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
        printf("Eroare la alocarea memoriei.\n");
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
Exemplu rulare:
input.txt:
13 15
1 2
1 3
1 4
2 5
2 6
4 7
4 8
5 9
5 10
7 12
9 11
12 13
*/

