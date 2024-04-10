#include <stdio.h>

typedef struct {
    int     numarMatricol;
    char    nume[30];
    int     grupa;
    char    practica;
    char    seminar;
    char    examen;
} Student;

void conversie();
void adaugaStudent();

void main()
{
    conversie();
    adaugaStudent();
    conversie();
}

void conversie()
{
    FILE *dat, *txt;
    dat = fopen("Fis_secv_Puncte.dat", "rb");
    if (dat == NULL)
    {
        printf("Eroare la deschiderea fisierului binar.");
    } else {
        txt = fopen("studenti.txt", "w");
        if (txt == NULL)
        {
            printf("Eroare la deschiderea fisierului text.");
        } else {
            Student student;
            fread(&student, sizeof(Student), 1, dat);
            fprintf(txt, "%4s %29s %4s %3s %4s %4s\n", "NRMAT", "NUME", "GRUPA", "P", "S", "E");

            while (!feof(dat))
            {
                fprintf(txt, "%4d %30s %4d %4d %4d %4d\n",
                    student.numarMatricol,
                    student.nume,
                    student.grupa,
                    student.practica,
                    student.seminar,
                    student.examen);
                fread(&student, sizeof(Student), 1, dat);
            }
            fclose(txt);
        }
        fclose(dat);
    }
}

void adaugaStudent()
{
    FILE *fisier;
    Student student;
    fisier = fopen("Fis_secv_Puncte.dat", "rb+");
    if (fisier == NULL)
    {
        printf("Eroare la deshiderea fisierului binar.");
        return;
    } else {
        int numarMatricol;
        fseek(fisier, 0, 0);
        printf("Introduceti numarul matricol: ");
        scanf("%d", &numarMatricol);
        while(numarMatricol != -1)
        {
            fseek(fisier, 0, 0);

            int gasit = 0;
            while(fread(&student, sizeof(Student), 1, fisier))
            {
                if (student.numarMatricol == numarMatricol)
                {
                    gasit = 1;
                    break;
                }
            }
            if (gasit)
            {
                printf("Studentul cu numarul matricol %d exista deja in fisier.\n", numarMatricol);
            } else {
                student.numarMatricol = numarMatricol;
                printf("Introduceti numele studentului: ");
                scanf("%s", student.nume);
                printf("Introduceti grupa studentului: ");
                scanf("%d", &student.grupa);
                student.practica = 0;
                student.seminar = 0;
                student.examen = 0;
                fseek(fisier, 0, 2);
                fwrite(&student, sizeof(Student), 1, fisier);
                printf("Student adaugat cu succes.\n");
            }
            printf("Introduceti numarul matricol: ");
            scanf("%d", &numarMatricol);
        }
    }
    fclose(fisier);
}