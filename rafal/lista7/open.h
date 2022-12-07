#include <stdio.h>
#include <stdlib.h>

#define defaultCapacity 1000

// Define the deque store structure
typedef struct deque_s {
  int* store;  // Pointer to the array holding the deque elements
  int size;   // Current number of elements in the deque
  int start;  // Index of the first element in the deque
  int end;    // Index of the last element in the deque
  int capacity;  // Maximum number of elements that the deque can hold
} Deque;

// Function prototypes
Deque new_Deque();
void del(Deque deque);
int size(Deque* deque);
int isEmpty(Deque deque);
int peek_left(Deque deque);
int deque_back(Deque* deque);
void deque_push_front(Deque* deque, int value);
void deque_push_back(Deque* deque, int value);
void deque_pop_front(Deque* deque);
void deque_pop_back(Deque* deque);

// Initialize a new deque with the given capacity
Deque new_Deque() {
  Deque* deque = (deque_s*) malloc(sizeof(Deque));
  deque->store = (int* ) malloc(defaultCapacity * sizeof(int));
  deque->size = 0;
  deque->start = 0;
  deque->end = -1;
  deque->capacity = defaultCapacity;
  return *deque;
}

// Free the memory used by the deque
void del(Deque deque) {
  free(deque.store);
  Deque *ptr = (deque_s*) deque;
  free(ptr);
}

// Return the number of elements in the deque
int size(Deque* deque) {
  return deque->size;
}

int isEmpty(Deque* deque) {
  return (deque->size == 0);
}

// Return the value of the front element in the deque
int peek_left(Deque* deque) {
  if (isEmpty(deque)) {
    printf("pusta tablica\n");
    return NULL;
  }
  return deque->store[deque->start];
}

// Return the value of the back element in the deque
int* deque_back(Deque deque) {
  if (isEmpty(&deque)) {
    printf("pusta tablica\n");
    return NULL;
  }
  return &deque.store[deque.start];
}

// Push a new value to the front of the deque
void deque_push_front(Deque* deque, int value) {
  if (deque->size == deque->capacity) {
    printf("Error: deque is full\n");
    exit(1);
  }
  deque->start = (deque->start - 1 + deque->capacity) % deque->capacity;
  deque->store[deque->start] = value;
  deque->size++;
}

// Push a new value to the back of the deque
void deque_push_back(Deque* deque, int value) {
  if (deque->size == deque->capacity) {
    printf("Error: deque is full\n");
    exit(1);
  }
  deque->end = (deque->end + 1) % deque->capacity;
  deque->data[deque->end] = value;
  deque->size++;
}

// Remove the front element from the deque
void deque_pop_front(Deque* deque) {
  if (deque_empty(deque)) {
    printf("Error: deque is empty\n");
    exit(1);
  }
  deque->start = (deque->start + 1) % deque->capacity;
  deque->size--;
}

// Remove the back element from the deque
void deque_pop_back(Deque* deque) {
  if (deque_empty(deque)) {
    printf("Error: deque is empty\n");
    exit(1);
  }
  deque->end = (deque->end - 1 + deque->capacity) % deque->capacity;
  deque->size--;
}
