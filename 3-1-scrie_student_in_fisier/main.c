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
    fclose(f);

    printf("Finalul scrierii fisierului binar\n");
    sleep(2);
    printf("Introdu numarul matricol de cautat: ");
    unsigned int nr_matricol_cautat;
    scanf("%u", &nr_matricol_cautat);
    short gasit = 0;
    f = fopen("studenti.bin", "rb");
    fseek(f,0,0); //rewind(f)
    fread(&s, 1, sizeof(s), f);
    while(!feof(f) && !gasit)
    {
        if (s.nr_matricol == nr_matricol_cautat)
        {
            printf("Studentul cu numarul matricol %u a fost gasit: %10s %10s \n", nr_matricol_cautat, s.nume, s.prenume);
            gasit = 1;
        }
        fread(&s, 1, sizeof(s), f);
    }
    fclose(f);

}