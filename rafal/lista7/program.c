#include <stdio.h>
#include "header.h"

int main()
{
    Deque tab = new_Deque();
    printf("cap = %d\n", tab->capacity);
    printf("^-deklaracja kolejki\n");
    for (int i = 10; i > 0; i--)
    {
        push_left(tab, i);
    }
    printf("size = %d\n", tab->size);
    printf("cap = %d\n", tab->capacity);
    printf("[%d] = %d\n", tab->start, *peek_left(tab));
    printf("[%d] = %d\n", tab->end, *peek_right(tab));
    printf("^-dodanie 10 wartosci od lewej\n");
    for (int i = 0; i < 10; i++)
    {
        push_right(tab, 11+i);
    }
    printf("size = %d\n", tab->size);
    printf("cap = %d\n", tab->capacity);
    printf("[%d] = %d\n", tab->start, *peek_left(tab));
    printf("[%d] = %d\n", tab->end, *peek_right(tab));
    printf("^-dodanie 10 wartosci od prawej\n");
    for (int i = 0; i < 5; i++)
    {
        pop_right(tab);
    }
    for (int i = 0; i < 11; i++)
    {
        pop_left(tab);
    }
    printf("size = %d\n", tab->size);
    printf("cap = %d\n", tab->capacity);
    printf("[%d] = %d\n", tab->start, *peek_left(tab));
    printf("[%d] = %d\n", tab->end, *peek_right(tab));
    printf("^-usuniecie 5ciu z prawej i 11 z lewej\n");
    for (int i = tab->start; i <= tab->end; i++)
    {
        printf("%d|%d\n", i, tab->store[i]);
    }
    printf("^-zawartosc kolejki\n");
    for (int i = 0; i < tab->capacity; i++)
    {
        printf("%d|%d\n", i, tab->store[i]);
    }
    printf("^-zawartosc calej pamieci\n");

    return 0;
}
