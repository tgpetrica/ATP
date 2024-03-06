#include <stdio.h>

typedef struct
{
    int             nr_matricol;
    char            nume[20];
    char            prenume[20];
    unsigned int    grupa;
    unsigned int    nr_note;
    unsigned int    note[10];
} student;

void main()
{
    FILE *f;
    f = fopen("studenti.bin", "w");
    if (f == NULL)
    {
        printf("Eroare la deschiderea fisierului");
        return;
    }
    student s;
    printf("Introduceti numarul matricol al studentului: ");
    scanf("%i", &s.nr_matricol);
    while (s.nr_matricol != -1)
    {
        printf("Introduceti numele studentului: ");
        getchar();
		gets(s.nume);
        printf("Introduceti prenumele studentului: ");
        getchar();
		gets(s.prenume);
        printf("Introduceti grupa studentului: ");
        scanf("%u", &s.grupa);
        printf("Introduceti numarul de note ale studetului: ");
        scanf("%u", &s.nr_note);
        printf("Introduceti notele studentului: ");
        for (int i = 0; i < s.nr_note; i++)
        {
            printf("Nota %u: ", (i + 1));
            scanf("%u", &s.note[i]);
        }
        fwrite(&s, 1, sizeof(s), f);
        printf("Introduceti numarul matricol al studentului: ");
        scanf("%i", &s.nr_matricol);
    }
}