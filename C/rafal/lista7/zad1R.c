#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int nOS(char *s){
    int c =0;
    int i = 0;
    while(s[i] != '\0'){
        //printf("%c", s[i]);
        if (s[i] == ' ')
        {
            c++;
        }
        
        i++;
    }
    return c;
}

void lPW(int *tab, char *s){
    int i = 0;
    int c = 0;
    int x = 0;
    while (s[i] != '\0')
    {
        if (s[i] != ' ')
        {
            c++;
        tab[x] = c;
        }else
        {
        x++;
        c = 0;
        }        
    i++;
    }
    
}

int len(char *s){
    int i = 0;
    while (s[i] != '\0')
    {
        i++;
    }
    return i;
}

char** split(char *s, int *z){
    int wrdLen[nOS(s)+1];
    lPW(&wrdLen[0], s);
    char **wynik;
    wynik = malloc(len(s)+1+nOS(s));
    *z = nOS(s)+1;
    int k = 0;
    for (int i = 0; i < nOS(s)+1; i++)
    {
            wynik[i] = malloc(wrdLen[i]+1);
            if (wynik[i] == NULL)
            {
                *z = -1;
                return NULL;
            }
            wynik[i][wrdLen[i]] = '\0';

        for (int j = 0; j < wrdLen[i]; j++)
        {
            wynik[i][j] = s[k];
            k++; 
        }
        k++;
    }

    
    return wynik;
}

int main(){
    char s[] = "ala ma kota hahahadcd fe ";
    int a = 9;
    char **wynik; 
    wynik = split(&s[0], &a);
    for (int i = 0; i < a; i++)
    {
        int j =0;
        while (wynik[i][j] != '\0')
        {
            printf("%c", wynik[i][j]);
            j++;
        }
        printf("\n");
    }
    
}