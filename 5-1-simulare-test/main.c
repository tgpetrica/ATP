#include <stdio.h>

typedef struct {
    int     nr_matricol;
    char    nume[30];
    int     grupa;
    char    practica;
    char    teme[10];
    char    examen;
    char    is; //0-1
} Student;

void conversie()
{
    FILE *bin, *text;

    bin = fopen("studenti.dat", "rb");
    if (bin == NULL)
    {
        printf("Eroare la deschiderea fisierului binar");
        return;
    } else {
        text = fopen("studenti.txt", "w");
        if (text == NULL)
        {
            printf("Eroare la deschiderea fisierului text");
            return;
        } else {
            Student student;
            fread(&student, sizeof(Student), 1, bin);
            fprintf(text, "NRMAT NUME GRUPA PRACTICA EXAMEN TEME\n");
            while (!feof(bin))
            {
                if (student.is == 1)
                {
                    fprintf(text, "%4d %30s %4d %4d %4d\n", student.nr_matricol, student.nume, student.grupa, student.practica, student.examen);
                    for (int i = 0; i < 10; i++)
                    {
                        fprintf(text, "%4d ", student.teme[i]);
                    }
                    fprintf(text, "\n");
                }
                fread(&student, sizeof(Student), 1, bin);
            }
            fclose(bin);
        }
        fclose(text);
    }
}

void modificare_articole()
{
    FILE *bin;
    Student student;
    bin = fopen("studenti.dat", "rb+");
    if (bin == NULL)
    {
        printf("Eroare la deschiderea fisierului binar");
        return;
    } else {
        int nr;
        printf("Introduceti numarul matricol al studentului: ");
        scanf("%d", &nr);
        while (nr != -1)
        {
            fseek(bin, nr * sizeof(Student), 0);
            fread(&student, sizeof(Student), 1, bin);
            if (student.is == 1)
            {
                printf("Introduceti noua nota a studentului: ");
                scanf("%d", &student.teme[5]);
                fseek(bin, ftell(bin) - sizeof(Student), 0);
                fwrite(&student, sizeof(Student), 1, bin);
            } else {
                printf("Articol nu exista");
            }
            printf("Introduceti numarul matricol al studentului: ");
            scanf("%d", &nr);
        }
        fclose(bin);
    }
}

void main()
{
    conversie();
    modificare_articole();

}