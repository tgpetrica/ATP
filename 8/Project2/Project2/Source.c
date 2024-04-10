/*
* Backtracking
* Problema turelor / reginelor
* 
* intr-o matrice patratica nxn
*/

#include <stdio.h>

int nr, v[100];

void backtracking(int k);
void afisare();
int validare(int k);
int solutie(int k);

void main()
{
	nr = 8;
	backtracking(1);
}

void backtracking(int k)	// k = pozitia curenta de completat din vectorul solutiei
{
	for (int i = 1; i <= nr; i++)
	{
		// valori posibile = index coloana
		v[k] = i;
		if (validare(k) == 1)
			if (solutie(k) == 1)
				afisare();
			else
				backtracking(k + 1);
	}
}

int validare(int k)
{
	for (int i = 1; i <= k - 1; i++)
		if (v[i] == v[k])
			return 0;
	return 1;
}

int solutie(int k)
{
	return (k == nr) ? 1 : 0;
}

void afisare()
{
	for (int i = 1; i <= nr; i++)
	{
		for (int j = 1; j <= nr; j++)
			if (v[i] == j)
				printf("T");
			else
				printf("-");
		printf("\n");
	}
	printf("\n____________\n\n");
}