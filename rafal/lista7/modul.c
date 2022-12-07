#include <stdio.h>
#include <stdlib.h>
#include "modul.h"

#define defaultCapacity 10
#define minimumCapacity 3

Deque new_Deque() {
  Deque* ptr = (Deque*) malloc(sizeof(Deque));
  Deque deque = *ptr;
  deque.store = (int* ) malloc(defaultCapacity * sizeof(int));
  deque.size = 0;
  deque.start = 0;
  deque.end = -1;
  deque.capacity = defaultCapacity;
  return deque;
}

void del(Deque deque) {
  free(deque.store);
  free(&deque);
}

int size(Deque deque) {
  return deque.size;
}

int isEmpty(Deque deque) {
  if (deque.size == 0)
  {
    return 1;
  }
  
  return 0;
}

int* peek_left(Deque deque) {
  if (isEmpty(deque)) {
    printf("pusta tablica\n");
    return NULL;
  }
  return &deque.store[deque.start];
}

int* peek_right(Deque deque) {
  if (isEmpty(deque)) {
    printf("pusta tablica\n");
    return NULL;
  }
  return &deque.store[deque.start];
}

int push_left(Deque deque, int value) {
  Deque *ptr;
  if (deque.size > deque.capacity/2) {
    if ((ptr = (Deque* ) realloc(&deque, defaultCapacity*2)) == NULL)
    {
      return 0;
    }
    deque = *ptr;
    deque.capacity *= 2;
    push_left(deque, value);
  }else{
    for (int i = deque.size; i > 0; i--)
    {
      deque.store[deque.start + i+1] = deque.store[deque.start+i];
    }
    deque.store[deque.start] = value;
    deque.size++;
  }
  return 1;
}

int push_right(Deque deque, int value) {
  Deque *ptr;
  if (deque.size > deque.capacity/2) {
    if ((ptr = (Deque* ) realloc(&deque, defaultCapacity*2)) == NULL)
    {
      return 0;
    }
    
    deque = *ptr;
    deque.capacity *= 2;
    push_right(deque, value);
  }else{
    deque.store[deque.end + 1] = value;
    deque.end++;
    deque.size++;
  }
  return 1;
}


int pop_left(Deque deque) {
  Deque *ptr;
  if (deque.size < deque.capacity/6)
  {
    ptr = (Deque* ) realloc(&deque, defaultCapacity/2);
    deque = *ptr;
    deque.capacity /= 6;
  }
  
  deque.start = deque.start + 1;
  deque.size--;
  return 1;
}

int pop_right(Deque deque) {
  Deque *ptr;
  if (deque.size < deque.capacity/6)
  {
    ptr = (Deque* ) realloc(&deque, defaultCapacity/2);
    deque = *ptr;
  }
  deque.capacity /= 6;
  
  deque.end = deque.end - 1;
  deque.size--;
  return 1;
}
