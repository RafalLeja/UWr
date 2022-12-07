typedef struct {
  int* store;  
  int size;  
  int start; 
  int end;    
  int capacity;  
} Deque;

Deque new_Deque();
void del(Deque deque);
int size(Deque deque);
int isEmpty(Deque deque);
int* peek_left(Deque deque);
int* peek_right(Deque deque);
int push_left(Deque deque, int value);
int push_right(Deque deque, int value);
int pop_left(Deque deque);
int pop_right(Deque deque);
