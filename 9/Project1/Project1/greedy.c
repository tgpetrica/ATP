#define _CRT_SECURE_NO_WARNINGS
#define N 10

#include <stdio.h>
/*
* - Metoda euristica
* - o singura solutie, optima
* 
* Rucsac capax 33 kg
* N obiecte = 10 -> capacitate (ci), castig (vi)
* obiect1 - 10kg, 20
* scopul: alegem obiecte astfel incat sa se incadreze
* in capacitatea maxima si sa obtinem profit maxim
* 
* pas1: sortam dupa castig unitar(vi raportat la ci)
*/
void rucsac(float c[], float v[], float CT, int sol);

void main()
{
	float CT = 33;
	float c[N] = { 1,2,3,4,5,6,7,8,9,10 };
	float v[N] = { 3,2,1,4,5,3,2,7,1,8 };
	int sol[N];

	// sortam dupa castig unitar vi/ci

	for(int i = 0; i < N - 1; i++)
		for (int j=i+1; j< N; j++)
			if (v[i] / c[i] < v[j] / c[j])
			{
				float aux = v[i];
				v[i] = v[j];
				v[j] = aux;

				aux = c[i];
				c[i] = c[j];
				c[j] = aux;

			}

	rucsac(c, v, CT, sol);

	float profitMaxim = 0;

	for (int i = 0; i < N; i++)
	{
		printf("%d ", sol[i]);
		profitMaxim += c[i];
	}
	printf("\nprofit maxim: %f", profitMaxim);

	

}

void rucsac(float c[], float v[], float CT, int sol[])
{
	float CR = CT; // capacitate ramasa
	for (int i = 0; i < N; i++)
	{
		if (CR >= c[i])
		{
			sol[i] = 1;
			CR -= c[i];
		}
		else {
			sol[i] = 0;
		}
	}
}
