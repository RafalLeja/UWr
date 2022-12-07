#include <stdio.h>

typedef struct DequeS
{
    int* store;
} * Deque;

Deque new_Deque(){
    Deque* que = malloc(sizeof(Deque));
    que->data = malloc(capacity * sizeof(int));
    que->size = 0;
    que->start = 0;
    que->end = -1;
    que->capacity = capacity;
    return que;
}

void del(Deque que){

}

int push_left(Deque que, int offset){

}

int push_right(Deque que, int offset){

}

int* peek_left(Deque que){

} 

int* peek_right(Deque que){
    
}

int pop_left(Deque que){

}

int pop_right(Deque que){
    
}

int len(Deque que){

}

int size(Deque que){

}