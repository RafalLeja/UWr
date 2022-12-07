#include <stdio.h>
#include "modul.h"

int main()
{
    Deque tab = new_Deque();
    printf("size = %d\n", tab.capacity);
    push_left(tab, 3);
    push_left(tab, 2);
    push_left(tab, 1);
    push_right(tab, 4);
    printf("size = %d\n", tab.size);
    printf("%d\n", *peek_left(tab));
    return 0;
}
