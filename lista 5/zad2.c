#include <stdio.h>

int equal(int right[], int left[]){
    int r = 0, l = 0;
    for (int i = 0; i < 10; i++)
    {
        r += right[i];
        l += left[i];
    }
    return (r - l);
}

void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubbleSort(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
 
        for (j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
}

void printTabs(int right[], int left[]){
    for (int i = 0; i < 10; i++)
    {
        printf("%d | %d", right[i], left[i]);
    }
    return 0;
}

int main(){
    int tab[10];
    int left[10];
    int right[10];
    for (int i = 0; i < 10; i++)
    {
        right[i] = 0;
        scanf("%d", &tab[i]);
        left[i] = tab[i];
        if (tab[i] > 100)
        {
            printf("podałeś zbyt dużą liczbe");
            return 0;
        }
    }
    bubbleSort(tab, 10);
    bubbleSort(left, 10);
    int rId = 0;
    int lId = 0;
    for (int i = 0; i < 10; i++)
    {
        right[i] = tab[i];
        for (int j = 0; j < 10; j++)
        {
            if (i != j)
            {
                if (equal(right,left) == 0)
                {
                    printTabs(right,left);
                    return 0;
                }
                
            }
            
        }
        
    }
    
    



    for (int i = 0; i < 10; i++)
    {
        printf("%d | %d | %d", tab[i], right[i], left[i]);
    }
    
}