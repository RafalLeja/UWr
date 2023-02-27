/* 
	* Rafał Leja
    * PO: lista 1, zadanie 2: tablica
	* gcc tablica.c 
*/

#include <stdio.h>
#include <math.h>
#include <string.h>

void tabliczka(float x1, float x2, float y1, float y2, float skok){
    int pre = 1, post = 1;
    for (int x = 0; x <= ((x2-x1)/skok)+1; x++)
    {
        for (int y = 0; y <= ((y2-y1)/skok)+1; y++)
        {
            float liczba = (x1 + (skok * (x)))*(y1 + (skok * (y)));
            int len = snprintf(NULL, 0, "%g", liczba);
            int tmp_pre = snprintf(NULL, 0, "%g", rint(liczba));
            int tmp_post = len - pre - 1;
            if(tmp_pre > pre) pre = tmp_pre;
            if(tmp_post > post) post = tmp_post;
        }
    }
    for (int x = 0; x <= ((x2-x1)/skok)+1; x++)
    {
        for (int y = 0; y <= ((y2-y1)/skok)+1; y++)
        {
            if (x == 0 && y == 0)
            {
                printf("%*c", pre+post+3, ' ');           
            }else if (x == 0)
            {
                printf("%*.*f ", pre+post+1, post, y1 + (skok * (y-1)));
            }else if (y == 0)
            {
                printf("%*.*f: ", pre+post+1, post, x1 + (skok * (x-1)));
            }else
            {
                printf("%*.*f ", pre+post+1, post, (x1 + (skok * (x-1)))*(y1 + (skok * (y-1))));
            }
        }
        printf("\n");
    }
}

int main(){
    tabliczka(0.2, 1.3, 0.2, 3.14, 0.33);
    return 0;
}