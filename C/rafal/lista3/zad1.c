#include <stdio.h>
#define VARCNT 4

int main(void)
{
    char v[2] = {'F', 'T'};
    int l = (1<<VARCNT) - 1;
    for (int i = l; i >= 0; i--)
    {
        int n = i;
        for (int j = VARCNT - 1; j >= 0; j--)
        {
            int p = n / (1<<j);
            printf("%c", v[p]);
            n = n % (1<<j);
            
        }
        printf("\n");
        
    }

    
    return 0;
}
