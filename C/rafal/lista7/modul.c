#include <stdio.h>
#include <stdlib.h>
#include "header.h"

#define defaultCapacity 10
#define minimumCapacity 3

Deque new_Deque() {
  Deque deque = malloc(sizeof(Deque));
  deque->store = (int* ) malloc(defaultCapacity * sizeof(int));
  deque->size = 0;
  deque->start = 0;
  deque->end = -1;
  deque->capacity = defaultCapacity;
  return deque;
}

void del(Deque deque) {
  free(deque->store);
}

int size(Deque deque) {
  return deque->capacity;
}

int len(Deque deque) {
  return deque->size;
}

int* peek_left(Deque deque) {
  if (deque->size == 0) {
    printf("pusta tablica\n");
    return NULL;
  }
  return &deque->store[deque->start];
}

int* peek_right(Deque deque) {
  if (deque->size == 0) {
    printf("pusta tablica\n");
    return NULL;
  }
  return &deque->store[deque->end];
}

int push_left(Deque deque, int value) {
  if (deque->size == 0)
  {
    deque->store[deque->start] = value;
    deque->size++;
    deque->end++;
    return 1;
  }
  
  if (deque->size > deque->capacity/2) {
    if ((deque->store = realloc(deque->store, deque->size*2*sizeof(int))) == NULL)
    {
      return 0;
    }
    deque->capacity *= 2;
    push_left(deque, value);
  }else{
    for (int i = deque->size; i > 0; i--)
    {
      deque->store[deque->start+i] = deque->store[deque->start+i-1];
    }
    deque->store[deque->start] = value;
    deque->size++;
    deque->end++;
  }
  return 1;
}

int push_right(Deque deque, int value) {
  if (deque->size > deque->capacity/2) {
    if ((deque->store = realloc(deque->store, deque->size*2*sizeof(int))) == NULL)
    {
      return 0;
    }
    deque->capacity *= 2;
    push_right(deque, value);
  }else{
    deque->end++;
    deque->store[deque->end] = value;
    deque->size++;
  }
  return 1;
}


int pop_left(Deque deque) {
  if (deque->size < (deque->capacity/6))
  {
    if ((deque->store = realloc(deque->store, (deque->capacity/2)*sizeof(int))) == NULL)
    {
      return 0;
    }
    deque->capacity /= 2;
  }
  
  deque->start += 1;
  deque->size--;
  return 1;
}

int pop_right(Deque deque) {
  if (deque->size < (deque->capacity/6))
  {
    if ((deque->store = realloc(deque->store, (deque->capacity/2)*sizeof(int))) == NULL)
    {
      return 0;
    }
  deque->capacity /= 2;
  }
  
  deque->end -= 1;
  deque->size--;
  return 1;
}
