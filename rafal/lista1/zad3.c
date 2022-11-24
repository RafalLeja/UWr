#include <stdio.h>

int main(void)
{
    unsigned int n;
    int start =0;
    scanf("%u", &n);
    unsigned int tab[45] = {1,2};
    for (int i = 2; i < 45; i++)
    {
        tab[i] = tab[i-1] + tab[i-2];
    }
    for (int i = 44; i >= 0; i--)
    {
        if (tab[i]<=n){
            printf("%c", '1');
            start = 1;
            n = n- tab[i];
        }
        else if (start ==1)
        {
            printf("%c", '0');
        }
        
    }
    
    return 0;
}
