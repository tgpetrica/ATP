#include <stdio.h>

typedef struct
{
    unsigned int    id;
    char            nume[20];
    char            prenume[20];
    unsigned int    grupa;
    unsigned int    note[5];
} student;

void citireStundet(student);
void afisareStudent(student);

void main()
{
    student s;
    citireStudent(&s);
    /*
    printf("Introduceti id-ul studentului: ");
    scanf("%d", &s.id);
    printf("Introduceti numele studentului: ");
    scanf("%s", s.nume);
    printf("Introduceti prenumele studentului: ");
    scanf("%s", s.prenume);
    printf("Introduceti grupa studentului: ");
    scanf("%d", &s.grupa);
    printf("Introduceti notele studentului: ");
    for (int i = 0; i < 5; i++)
    {
        printf("Nota %d: ", (i + 1));
        scanf("%d", &s.note[i]);
    }
    */
    afisareStudent(s);
    
    

}

void citireStudent(student *s)
{
    printf("Introduceti id-ul studentului: ");
    scanf("%d", &s->id);
    printf("Introduceti numele studentului: ");
    scanf("%s", s->nume);
    printf("Introduceti prenumele studentului: ");
    scanf("%s", s->prenume);
    printf("Introduceti grupa studentului: ");
    scanf("%d", &s->grupa);
    printf("Introduceti notele studentului: ");
    for (int i = 0; i < 5; i++)
    {
        printf("Nota %d: ", (i + 1));
        scanf("%d", &s->note[i]);
    }
}

void afisareStudent(student s)
{
    printf("Studentul %s %s are id-ul %d, este in grupa %d si are notele: ", s.nume, s.prenume, s.id, s.grupa);
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", s.note[i]);
    }
    printf("\n");
}
