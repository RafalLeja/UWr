#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct punkt
{
    int x;
    int y;
} Punkt;

struct wynik
{
    double obwod;
    struct punkt a;
    struct punkt b;
    struct punkt c;
} Wynik;

int porownajY(const void *p1, const void *p2)
{
    struct punkt *a = (struct punkt *)p1;
    struct punkt *b = (struct punkt *)p2;
    if (a->y == b->y)
    {
        return a->x < b->x;
    }
    return a->y < b->y;
}

int porownajX(const void *p1, const void *p2)
{
    struct punkt *a = (struct punkt *)p1;
    struct punkt *b = (struct punkt *)p2;
    if (a->x == b->x)
    {
        return a->y < b->y;
    }
    return a->x < b->x;
}

double obwod(struct punkt p1, struct punkt p2, struct punkt p3)
{
    double x1 = p1.x;
    double x2 = p2.x;
    double x3 = p3.x;
    double y1 = p1.y;
    double y2 = p2.y;
    double y3 = p3.y;

    double bok1 = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    double bok2 = sqrt(pow(x3 - x2, 2) + pow(y3 - y2, 2));
    double bok3 = sqrt(pow(x1 - x3, 2) + pow(y1 - y3, 2));
    return bok1 + bok2 + bok3;
}

struct wynik sprawdzenie1(struct punkt *punkty, int rozmiar)
{
    struct wynik wynik;
    wynik.obwod = INFINITY;
    for (int i1 = 0; i1 < rozmiar; i1++)
    {
        for (int i2 = 0; i2 < rozmiar; i2++)
        {
            for (int i3 = 0; i3 < rozmiar; i3++)
            {
                if (i3 != i2 && i3 != i1 && i2 != i1)
                {
                    struct wynik temp;
                    temp.obwod = obwod(punkty[i1], punkty[i2], punkty[i3]);
                    temp.a = punkty[i1];
                    temp.b = punkty[i2];
                    temp.c = punkty[i3];
                    wynik = (wynik.obwod < temp.obwod) ? wynik : temp;
                }
            }
        }
    }
    return wynik;
}

struct wynik sprawdzenie2(struct punkt *punkty_y, int rozmiar, double v, int xsrodek)
{
    struct punkt *temp = calloc(rozmiar, sizeof(struct punkt));
    struct wynik wynik;
    wynik.obwod = INFINITY;
    int start = 0;
    int end = 0;

    for (int i = 0; i < rozmiar; i++) {
        if (abs(punkty_y[i].x - xsrodek) > v)
        {
            continue;        
        }
        while (start < end && punkty_y[i].y - temp[start].y > (v*2))
        {
            start++;
        }
        for (int i2 = start; i2 < end; i2++) {
            for (int i3 = i2+1; i3 < end; i3++) {
                struct wynik temp;
                temp.obwod = obwod(punkty_y[i], punkty_y[i2], punkty_y[i3]);
                if (temp.obwod < wynik.obwod) {
                    temp.a = punkty_y[i];
                    temp.b = punkty_y[i2];
                    temp.c = punkty_y[i3];
                    wynik = temp;
                }
            }
        }
        temp[end++] = punkty_y[i];
    }
    free(temp);
    return wynik;
}

struct wynik najmniejszyObwod(struct punkt *punkty, struct punkt *punkty_y, int dol, int gora)
{
    struct wynik mininum;
    int zakres = gora - dol;
    if (zakres < 3)
    {
        mininum.obwod = INFINITY;
        return mininum;
    }

    int srodek = dol + zakres / 2;
    printf("srodek: %d\n", srodek);
    double xsrodek = (punkty[srodek].x + punkty[srodek + 1].x) / 2.0;
    struct punkt punktSrodek = {xsrodek, (punkty[srodek].y + punkty[srodek + 1].y) / 2.0}; 

    printf("lewy %d, prawy %d\n", srodek, gora - srodek);
    struct punkt *lewyY = malloc(srodek * sizeof(struct punkt));
    struct punkt *prawyY = malloc((gora - srodek) * sizeof(struct punkt));

    int l = 0;
    int r = 0;
    for (int i = 0; i < zakres; i++) {
        printf("punkty_y[%d]: (%d,%d), xsrodek: %lf\n", i, punkty_y[i].x, punkty_y[i].y, xsrodek);
        if (porownajX(&punkty_y[i], &punktSrodek)) {
            lewyY[l++] = punkty_y[i];
        } else {
            prawyY[r++] = punkty_y[i]; 
        }
    }
    printf("l: %d, r: %d\n", l, r);

    struct wynik polowa1 = najmniejszyObwod(punkty, lewyY, dol, srodek);
    struct wynik polowa2 = najmniejszyObwod(punkty, prawyY, srodek + 1, gora);
    mininum = (polowa1.obwod < polowa2.obwod) ? polowa1 : polowa2;
    double v = mininum.obwod / 2;

    // struct punkt *temp = malloc(zakres * sizeof(struct punkt));
    // int tempRozmiar = 0;
    // int start = 0;

    // for (int i = dol; i < gora; i++)
    // {
    //     if (abs(punkty_y[i].x - xsrodek) < v)
    //     {
    //         temp[tempRozmiar++] = punkty_y[i];
    //     }
    // }
    // struct wynik sprawdzenie = sprawdzenie2(punkty_y, zakres, v, xsrodek);
    
    printf("zakres: %d\n", zakres);
    struct punkt *temp = calloc(zakres, sizeof(struct punkt));
    // struct wynik wynik;
    // wynik.obwod = INFINITY;
    int start = 0;
    int end = 0;

    for (int i = 0; i < zakres; i++) {
        if (abs(punkty_y[i].x - xsrodek) > v)
        {
            continue;        
        }
        while (start < end && punkty_y[i].y - temp[start].y > v)
        {
            start++;
        }
        for (int i2 = start; i2 < end; i2++) {
            for (int i3 = i2+1; i3 < end; i3++) {
                struct wynik tempWynik;
                tempWynik.obwod = obwod(punkty_y[i], temp[i2], temp[i3]);
                if (tempWynik.obwod < mininum.obwod) {
                    tempWynik.a = punkty_y[i];
                    tempWynik.b = temp[i2];
                    tempWynik.c = temp[i3];
                    mininum = tempWynik;
                }
            }
        }
        temp[end++] = punkty_y[i];
    }
    // free(temp);
    
    // mininum = (mininum.obwod < sprawdzenie.obwod) ? mininum : sprawdzenie;
    free(temp);
    free(lewyY);
    free(prawyY);        
    return mininum;
}

int main()
{
    int n;
    scanf("%d", &n);
    struct punkt *punkty = malloc(n * sizeof(struct punkt));
    struct punkt *punkty_y = malloc(n * sizeof(struct punkt));
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &punkty[i].x, &punkty[i].y);
        punkty_y[i] = punkty[i];
    }

    qsort(punkty, n, sizeof(struct punkt), porownajX);
    qsort(punkty_y, n, sizeof(struct punkt), porownajY);

    struct wynik result = najmniejszyObwod(punkty, punkty_y, 0, n);
    printf("%d %d\n", result.a.x, result.a.y);
    printf("%d %d\n", result.b.x, result.b.y);
    printf("%d %d\n", result.c.x, result.c.y);

    free(punkty);
    free(punkty_y);
    return 0;
}
