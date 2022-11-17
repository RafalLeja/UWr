#include <stdio.h>

typedef long Word;


int main(){
    Word w;
    int p = &w;
    printf("%d %d %p", w, *p, &w);
}