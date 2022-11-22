#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    int tab[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &tab[i]);
    }
    for (int i = 0; i < n; i++)
    {
        int minId = i;
        for (int j = i+1; j < n; j++){
            if (tab[j] < tab[minId]){
                minId = j;}
 
            if(minId != i){
                int temp = tab[i];
                tab[i] = tab[minId];
                tab[minId] = temp;
            }
        
    }}
    for (int i = 0; i < n; i++)
    {
        printf("%d", tab[i]);
    }
    return 0;
}