#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#define INF 1000000

typedef struct {
    float l;
    int vf;
}eticheta;

//subprogram
//preia datele unui graf in forma tabelara din fisierul nume si obtine
//matricea ponderilor, unde INF este valoarea cu semnificatie de infinit
//ultima linie a fisierului contine virful initial din algoritmul Dijkstra

//subprogram
//functia pentru implementarea algoritmului Dijkstra - returneaza
//vectorul de etichete

//subprogram
//functia principala

void preia_graf(char* nume, float*** w, int* n, int* v0)
{
    int i, j, m, u, v; float p;
    FILE* f = fopen(nume, "rt");
    fscanf(f, "%i", n);

    float** mw = (float**)malloc(*n * sizeof(float*));
    for (i = 0; i < *n; i++)
        mw[i] = (float*)malloc(*n * sizeof(float));

    fscanf(f, "%i", &m);

    for (i = 0; i < *n; i++)
        for (j = 0; j < *n; j++)
            mw[i][j] = INF;

    for (i = 0; i < m; i++)
    {
        fscanf(f, "%i", &u);
        fscanf(f, "%i", &v);
        fscanf(f, "%f", &p);
        mw[u - 1][v - 1] = mw[v - 1][u - 1] = p;
    }

    fscanf(f, "%i", v0);
    fclose(f);
    *w = mw;
}

eticheta* Dijkstra(float** w, int n, int v0)
{
    int i, * prel, nrit, ui, v, vmin;
    float lmin;
    eticheta* v_et = (eticheta*)malloc(n * sizeof(eticheta));

    for (i = 0; i < n; i++)
        v_et[i].l = INF;
    v_et[v0 - 1].l = 0;

    prel = (int*)malloc(n * sizeof(int));
    //vector cu proprietatea prel[i]=1 daca pentru virful i+1 a
    //fost deja determinat un drum de cost minim
    //prel[i]=0 in caz contrar

    for (i = 0; i < n; i++)
        prel[i] = 0;
    prel[v0 - 1] = 1;

    ui = v0;
    for (nrit = 0; nrit < n - 1; nrit++)
    {
        lmin = INF;
        //sunt recalculate w-distantele de la virfurile v cu prel[v-1]=0 si este determinat vmin, //urmatorul virf cu proprietatea ca pentru acesta a fost determinat un drum de cost minim,
        // lmin
        for (v = 1; v <= n; v++)
        {
            if ((prel[v - 1] == 0) && (v_et[v - 1].l > v_et[ui - 1].l + w[v - 1][ui - 1]))
            {
                v_et[v - 1].l = v_et[ui - 1].l + w[v - 1][ui - 1];
                v_et[v - 1].vf = ui;
            }
            if ((prel[v - 1] == 0) && v_et[v - 1].l < lmin)
            {
                lmin = v_et[v - 1].l;  vmin = v;
            }
        }
        ui = vmin; prel[ui - 1] = 1;
    }
    free(prel); return v_et;
}
void main()
{
    float** w;
    int n, v0, v, u, i;
    char numef[20];
    printf("Introduceti numele fisierului care contine graful:");
    scanf("%s", numef);
    preia_graf(numef, &w, &n, &v0);
    eticheta* rez = Dijkstra(w, n, v0);
    for (v = 1; v <= n; v++)
        if (v != v0)
        {
            printf("Costul unui cel mai ieftin drum de la %i la %i este %8.3f", v, v0, rez[v - 1].l);
            printf("\n Un drum de cost minim: %i ", v);
            u = v;
            while (rez[u - 1].vf != v0)
            {
                printf("%i ", rez[u - 1].vf);
                u = rez[u - 1].vf;
            }
            printf("%i \n\n", v0);
        }
    free(rez);
    for (i = 0; i < n; i++) free(w[i]);
    free(w);
}