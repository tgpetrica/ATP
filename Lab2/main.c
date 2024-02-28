#include <stdio.h>

void main()
{
    FILE *f = fopen("fisier.txt", "w");
    int vector[20], n;
    printf("Scrie dimensiunea vectorului: ");
    scanf("%i", &n);

    for (int i = 0; i < n; i++)
    {
        scanf("%i", &vector[i]);
        fprintf(f, "%i 5", vector[i]);
    }
    fclose(f);

}