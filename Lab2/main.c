#include <stdio.h>

void main()
{
    FILE *f = fopen("fisier.txt", "w");
    if (!f) // f == NULL
    {
        printf("Nu s-a putut creea fisierul.");
    }

    int vector[20], n;
    printf("Scrie dimensiunea vectorului: ");
    scanf("%i", &n);

    for (int i = 0; i < n; i++)
    {
        scanf("%i", &vector[i]);
        fprintf(f, "%i ", vector[i]);
    }
    fclose(f);

}