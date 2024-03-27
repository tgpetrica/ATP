#include <stdio.h>

typedef struct {
    int     nr_matricol;
    char    nume[30];
    int     grupa;
    char    practica;
    char    activitate;
    char    examen;
} Student;

void conversie();
void modificare_articole();

void main()
{
    conversie();
    modificare_articole();
}

void conversie()
{
    FILE *bin, *text;
    bin = fopen("studenti.dat", "rb");
    if (bin == NULL)
    {
        printf("Eroare la deschiderea fisierului binar");
    } else {
        text = fopen("studenti.txt", "w");
        if (text == NULL)
        {
            printf("Eroare la deschiderea fisierului text");
        } else {
            Student student;
            fread(&student, sizeof(Student), 1, bin);
            while (!feof(bin))
            {
                fprintf(text, "%4d %30s %4d %4d %4d %4d\n", 
                    student.nr_matricol, 
                    student.nume, 
                    student.grupa, 
                    student.practica, 
                    student.activitate, 
                    student.examen);
                fread(&student, sizeof(Student), 1, bin);
            }

            fclose(text);
        }
        fclose(bin);
    }
}

void modificare_articole()
{
    FILE *fisier;
    Student student;
    fisier = fopen("studenti.dat", "rb+");
    if (fisier == NULL)
    {
        printf("Eroare la deschiderea fisierului text");
    } else {
        int nr;
        printf("Introduceti numarul matricol al studentului: ");
        scanf("%d", &nr);

        int gasit = 0;
        while (nr != -1)
        {
            gasit = 0;
            fseek (fisier, 0, 0);
            fread(&student, sizeof(Student), 1, fisier);
            while (!feof(fisier) && gasit == 0)
            {
                if (student.nr_matricol == nr)
                {
                    gasit = 1;
                    printf("Introduceti noua nota: ");
                    scanf("%d", &student.examen);
                    fseek(fisier, ftell(fisier) - sizeof(Student), 0);
                    fwrite(&student, sizeof(Student), 1, fisier);
                    
                }
                fread(&student, sizeof(Student), 1, fisier);
            }
            if (gasit == 0)
            {
                printf("Studentul nu a fost gasit\n");
            }
            printf("Introduceti numarul matricol al studentului: ");
            scanf("%d", &nr);
        }
        fclose(fisier);
    }
}