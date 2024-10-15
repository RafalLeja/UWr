#include "csapp.h"

// pthread_mutex_t output_mutex;
pthread_mutex_t output_mutex = PTHREAD_MUTEX_INITIALIZER;


static int ndselect(int n) {
  /* TODO: A loop is missing here that spawns processes and waits for them! */
  pid_t pids[9];
  for(int i = 0; i < n; i++){
    pids[i] = Fork();
    if(pids[i] == 0){
      return i;
    }
  }
  for(int i = 0; i < 9; i++){
    waitpid(pids[i], NULL, 0);
  }
  exit(0);
}

static int conflict(int x1, int y1, int x2, int y2) {
  return x1 == x2
    || y1 == y2
    || x1 + y1 == x2 + y2
    || x1 - y1 == x2 - y2;
}

static void print_line_sep(int size) {
  for (int i = 0; i < size; ++i) 
    printf("+---");
  printf("+\n");
}

static void print_board(int size, int board[size]) {
  pthread_mutex_lock(&output_mutex);

  for (int i = 0; i < size; ++i) {
    print_line_sep(size);
    for (int j = 0; j < size; ++j)
      printf("|%s", board[i] == j ? " Q " : "   ");
    printf("|\n");
  }
  print_line_sep(size);
  printf("\n");

  fflush(stdout);

  pthread_mutex_unlock(&output_mutex);
}

int main(int argc, char **argv) {
  if (argc != 2)
    app_error("Usage: %s [SIZE]", argv[0]);

  int size = atoi(argv[1]);

  if (size < 3 || size > 9)
    app_error("Give board size in range from 4 to 9!");

  int board[size];

  // if(pthread_mutex_init(&output_mutex, NULL) != 0){
  //   perror("problem z mutexem");
  //   exit(1);
  // }

  /* TODO: A loop is missing here that initializes recursive algorithm. */
  for(int i = 0; i < size; i++){
    int next = ndselect(size);
    if(next < 0 || next > size){
      exit(0); //coś poszło nie tak
    }
    board[i] = next;
    for(int j = 0; j < i; j++){
      if(conflict(j, board[j], i, board[i])){
        exit(0);
      }
    }
  }
  print_board(size, board);

  return 0;
}
