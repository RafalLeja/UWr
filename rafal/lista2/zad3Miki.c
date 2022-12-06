#include<stdio.h>
#include<stdlib.h>

int tab[105][105];
long long szyszki;

void wczytaj(int w, int h)
{
    for(int i=0; i<h; i++)
    {
        for(int j=0; j<w; j++)
        {
            char c;
            if(scanf(" %c",&c)!=1)
            {
                continue;
            }
            if(c>='1' && c<='9')
            {
                tab[i][j]=c-'0';
            }
            else
            {
                continue;
            }
        }
    }
}

int wschod(int w, int h)
{
    long long sz=0;
    for(int i=0; i<h; i++)
    {
        int cien=0;
        for(int j=w-1; j>=0; j--)
        {
            int wys=tab[i][j];
            if(cien==0)
            {
                if(wys==9)
                {
                    sz++;
                    cien=9;
                }
                else if(wys>0)
                {
                    cien=wys;
                    tab[i][j]++;
                }
            }
            else
            {
                if(wys>=cien)
                {
                    cien=wys;
                }
                else
                {
                    cien--;
                }
            }
        }
    }
    szyszki+=sz;
    return sz;
}

int poludnie(int w, int h)
{
    long long sz=0;
    for(int i=0; i<w; i++)
    {
        int cien=0;
        for(int j=h-1; j>=0; j--)
        {
            int wys=tab[j][i];
            if(cien==0)
            {
                if(wys==9)
                {
                    sz++;
                    cien=9;
                }
                else if(wys>0)
                {
                    cien=wys;
                    tab[j][i]++;
                }
            }
            else
            {
                if(wys>=cien)
                {
                    cien=wys;
                }
                else
                {
                    cien--;
                }
            }
        }
    }
    szyszki+=sz;
    return sz;
}

int zachod(int w, int h)
{
    long long sz=0;
    for(int i=0; i<h; i++)
    {
        int cien=0;
        for(int j=0; j<w; j++)
        {
            int wys=tab[i][j];
            if(cien==0)
            {
                if(wys==9)
                {
                    sz++;
                    cien=9;
                }
                else if(wys>0)
                {
                    cien=wys;
                    tab[i][j]++;
                }
            }
            else
            {
                if(wys>=cien)
                {
                    cien=wys;
                }
                else
                {
                    cien--;
                }
            }
        }
    }
    szyszki+=sz;
    return sz;
}

int main()
{
    long long w,h,d,sz=0;                  
    scanf("%lld %lld %lld",&w,&h,&d);
    wczytaj(w,h);
    if(d<20)
    {
        for(int i=0; i<d; i++)
        {
            sz+=wschod(w,h);
            sz+=poludnie(w,h);
            sz+=zachod(w,h);
        }
    }
    else
    {
        for(int i=0; i<19; i++)
        {
            wschod(w,h);
            poludnie(w,h);
            zachod(w,h);
        }
        long long wsch,popo,zach;
        wsch=wschod(w,h);
        popo=poludnie(w,h);
        zach=zachod(w,h);
        long long ilosc=wsch+popo+zach;
        szyszki+=ilosc*(d-20);
    }
    printf("%lld",szyszki);
    return 0;
}