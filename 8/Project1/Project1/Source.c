/*
* Recursivitate
* - metoda reducerii (de la n -> n-1)
* - metoda descompunerii (divide et impera - cautare binara)
*	ls ld
* 
* ex1. sa se scrie subprogramul recursiv care determina 
* numarul de elemente negative dintr-un vector
* 
* ex.2 sa se scrie subprogramul recursiv care determina
* suma elementelor impare dintr-un vector
* 
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int numara(int n, int v[]);

int DeI(int ls, int ld, int v[]);

void main()
{
	int nr, v[100], i;
	printf("Numarul este: ");
	scanf("%d", &nr);

	for (i = 0; i < nr; i++)
	{
		printf("\nv[%d] = ", i);
		scanf("%d", &v[i]);
	}

	printf("\nNumar elemente negative: %d", numara(nr, v));
	printf("\nNumar elemente negative prin DeI: %d", DeI(0, nr - 1, v));
	printf("\n=+=+=+=+=+=+=+=+=+=+=+=+=+=\n");
	printf("Suma 1: %d", suma(nr, v));
	printf("\nSuma 2: %d", sumaDeI(0, nr, v));

}

//metoda reducerii

int numara(int nr, int v[])
{
	int contor;
	if (nr == 0)
		contor = 0;
	else
	{
		contor = (v[nr - 1] < 0) ? 1 : 0;
		contor += numara(nr - 1, v);
	}
	return contor;
}

//metoda reducerii

int suma(int nr, int v[])
{
	if (nr == 0)
		return 0;
	else
		return ((v[nr - 1] % 2 == 1) ? v[nr - 1] : 0) +
		suma(nr - 1, v);
}

// metoda DeI

int DeI(int ls, int ld, int v[])
{
	int contor;
	if (ls == ld)
		contor = (v[ls] < 0) ? 1 : 0;
	else
	{
		contor = DeI(ls, (ls + ld) / 2, v) + DeI((ls + ld) / 2 + 1, ld, v);
	}
	return contor;
}


int sumaDeI(int ls, int ld, int v[])
{
	if (ls == ld)
		return (v[ls] % 2 == 1) ? v[ls] : 0;
	else
		return sumaDeI(ls, (ls + ld) / 2, v) + sumaDeI((ls + ld) / 2 + 1, ld, v);
}