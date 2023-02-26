#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    int nast, wyraz = 1;
    int ilość = 0, poprzedni = 0, potęga = 1;
    for (int i = 0; i < n; i++)
    {
        printf("%d: %d\n", i+1, wyraz);
        while (wyraz > 0)
        {
            if (wyraz % 10 != poprzedni){
                
            }
            switch (wyraz % 10)
            {
            case 1:
                ilość++;
                poprzedni = 1;
                break;

            case 2:
                ilość++;
                poprzedni = 2;
                break;

            case 2:
                ilość++;
                poprzedni = 2;
                break;
            wyraz /= 10;
            }    
        }
        
    }
    
}