#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void royWarshall(int a[10][10], int nn, int mat[10][10]);

int conexitate(int nn, int mat[10][10]);

void main()
{
	int nn, nm, a[10][10], vi, vf, mat[10][10];
	printf("Numar nodurilor: ");
	scanf("%d", &nn);

	printf("Numar muchiilor: ");
	scanf("%d", &nm);

	for (int i = 0; i < nn; i++)
		for (int j = 0; j < nn; j++)
			a[i][j] = 0;

	for (int i = 0; i < nm; i++)
	{
		scanf("%d", &vi);
		scanf("%d", &vf);
		a[vi - 1][vf - 1] = a[vf - 1][vi - 1] = 1;
	}

	for (int i = 0; i < nn; i++)
	{
		for (int j = 0; j < nn; j++)
			printf("%d ", a[i][j]);
		printf("\n");
	}

	//determinare matricei existentei drumurilor
	// alg Roy-Warshall

	royWarshall(a, nn, mat);
	printf("\n\n");
	for (int i = 0; i < nn; i++)
	{
		for (int j = 0; j < nn; j++)
			printf("%d ", mat[i][j]);
		printf("\n");
	}

	//determinare graf conex
	int conex = conexitate(nn, mat);
	if (conex == 1)
		printf("graful este conex");
	else
		printf("graful nu este conex");
}

void royWarshall(int a[10][10], int nn, int mat[10][10])
{
	for (int i = 0; i < nn; i++)
		for (int j = 0; j < nn; j++)
			mat[i][j] = a[i][j];

	for (int j = 0; j < nn; j++)
		for (int i = 0; i < nn; i++)
			if (mat[i][j] == 1)
				for (int k = 0; k < nn; k++)
					if (mat[i][k] == 0 && mat[j][k] == 1) // mat[i][k] < mat[j][k]
						mat[i][k] = mat[j][k];
}

int conexitate(int nn, int mat[10][10])
{
	for (int i = 0; i < nn; i++)
		for (int j = 0; j < nn; j++)
			if (mat[i][j] == 0)
				return 0;
	return 1;
}
