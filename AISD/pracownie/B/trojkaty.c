#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct point
{
    int x;
    int y;
} Punkt;

struct wynik
{
    double obwod;
    struct point a;
    struct point b;
    struct point c;
} Wynik;

int porownajY(const void *p1, const void *p2)
{
    struct point *a = (struct point *)p1;
    struct point *b = (struct point *)p2;
    return a->y < b->y;
}

int porownajX(const void *p1, const void *p2)
{
    struct point *a = (struct point *)p1;
    struct point *b = (struct point *)p2;
    return a->x < b->x;
}

double obwod(struct point p1, struct point p2, struct point p3)
{
    long long x1 = p1.x;
    long long x2 = p2.x;
    long long x3 = p3.x;
    long long y1 = p1.y;
    long long y2 = p2.y;
    long long y3 = p3.y;

    double bok1 = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    double bok2 = sqrt(pow(x3 - x2, 2) + pow(y3 - y2, 2));
    double bok3 = sqrt(pow(x1 - x3, 2) + pow(y1 - y3, 2));
    return bok1 + bok2 + bok3;
}

struct wynik sprawdzenie1(struct point *punkty, int rozmiar)
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

struct wynik sprawdzenie2(struct point *punkty_y, int rozmiar, double v, int xsrodek)
{
    struct point *temp = calloc(rozmiar, sizeof(struct point));
    struct wynik wynik;
    wynik.obwod = INFINITY;
    int start = 0;
    int end = 0;
    // for (int i = 0; i < rozmiar; i++)
    // {
    //     int tempRozmiar = 0;
    //     temp[tempRozmiar++] = punkty[i];
    //     int j = i + 1;
    //     while (punkty[j].y <= punkty[i].y + v && j < rozmiar)
    //     {
    //         temp[tempRozmiar++] = punkty[j];
    //         j++;
    //     }
    //     if (tempRozmiar >= 3)
    //     {
    //         struct wynik sprawdzenie = sprawdzenie1(temp, tempRozmiar);
    //         wynik = (wynik.obwod < sprawdzenie.obwod) ? wynik : sprawdzenie;
    //     }
    // }

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
                temp.a = punkty_y[i];
                temp.b = punkty_y[i2];
                temp.c = punkty_y[i3];
                wynik = (wynik.obwod < temp.obwod) ? wynik : temp;
            }
        }
        temp[end++] = punkty_y[i];
    }
    free(temp);
    return wynik;
}

struct wynik najmniejszyObwod(struct point *punkty, struct point *punkty_y, int dol, int gora)
{
    struct wynik mininum;
    int zakres = gora - dol;
    if (zakres < 3)
    {
        mininum.obwod = INFINITY;
        return mininum;
    }

    int srodek = dol + zakres / 2;
    int xsrodek = (punkty[srodek].x + punkty[srodek + 1].x) / 2;

    struct point *lewyY = malloc(srodek * sizeof(struct point));
    struct point *prawyY = malloc((gora - srodek) * sizeof(struct point));

    int l = 0;
    int r = 0;
    for (int i = dol; i < gora; i++) {
        if (punkty_y[i].x > xsrodek) {
            prawyY[r++] = punkty_y[i]; 
        } else {
            lewyY[l++] = punkty_y[i];
        }
    }

    struct wynik polowa1 = najmniejszyObwod(punkty, lewyY, dol, srodek);
    struct wynik polowa2 = najmniejszyObwod(punkty, prawyY, srodek + 1, gora);
    mininum = (polowa1.obwod < polowa2.obwod) ? polowa1 : polowa2;
    double v = mininum.obwod / 2;

    struct point *temp = malloc(zakres * sizeof(struct point));
    int tempRozmiar = 0;
    // int start = 0;

    for (int i = dol; i < gora; i++)
    {
        if (abs(punkty_y[i].x - xsrodek) < v)
        {
            temp[tempRozmiar++] = punkty_y[i];
        }
    }
    struct wynik sprawdzenie = sprawdzenie2(punkty_y, zakres, v, xsrodek);
    mininum = (mininum.obwod < sprawdzenie.obwod) ? mininum : sprawdzenie;
    free(temp);

    return mininum;
}

int main()
{
    int n;
    scanf("%d", &n);
    struct point *punkty = malloc(n * sizeof(struct point));
    struct point *punkty_y = malloc(n * sizeof(struct point));
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &punkty[i].x, &punkty[i].y);
        punkty_y[i] = punkty[i];
    }

    qsort(punkty, n, sizeof(struct point), porownajX);
    qsort(punkty_y, n, sizeof(struct point), porownajY);

    struct wynik result = najmniejszyObwod(punkty, punkty_y, 0, n);
    printf("%d %d\n", result.a.x, result.a.y);
    printf("%d %d\n", result.b.x, result.b.y);
    printf("%d %d\n", result.c.x, result.c.y);

    free(punkty);
    free(punkty_y);
    return 0;
}
