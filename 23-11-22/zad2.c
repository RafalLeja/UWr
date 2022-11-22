#include <stdio.h>

typedef long Word;


int main(){
    int tab[10];
    for (int i = 0; i < 10; i++)
    {
        scanf("%d", &tab[i]);
        if (tab[i] >= 100)
        {
            printf("podałeś liczbe większą niż 100");
            return 0;
        }
        
    }
     
}