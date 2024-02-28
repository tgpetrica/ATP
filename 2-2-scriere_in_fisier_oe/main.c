#include <stdio.h>

void main()
{
    int vector[20], n;
    printf("Scrie numarul de elemente: ");
    scanf("%i", &n);

    for (int i = 0; i < n; i++)
    {
        scanf("%i", &vector[i]);
    }

    FILE *impar, *par;
    impar = fopen("impare.txt", "w");
    par = fopen("par.txt","w");

    if (!impar || !par)
    {
        printf("Fisierul nu poate fi creat.");
    }
    else {

        for (int i = 0; i < n; i++)
        {
            if (vector[i] % 2 == 0)
            {
                fprintf(par, "%i ", vector[i]);
            }
            else {
                fprintf(impar, "%i ", vector[i]);
            }

        }
    }
    fclose(impar);
    fclose(par);
}