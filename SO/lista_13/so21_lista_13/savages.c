#include "csapp.h"

static __unused void outc(char c) {
  Write(STDOUT_FILENO, &c, 1);
}

#define N 10
#define M 5

static struct {
  /* TODO: Put semaphores and shared variables here. */
  int posilki;
  sem_t przyGarnku;
  sem_t budzik;
  sem_t pelny;
} *shared = NULL;


static void savage(void) {
  for (;;) {
    /* TODO Take a meal or wait for it to be prepared. */
    Sem_wait(&shared->przyGarnku);
    if (shared->posilki == 0) {
      Sem_post(&shared->budzik);
      Sem_wait(&shared->pelny);
    }
    shared->posilki--;
    Sem_post(&shared->przyGarnku);
    /* Sleep and digest. */
    usleep(rand() % 1000 + 1000);
  }

  exit(EXIT_SUCCESS);
}

static void cook(void) {
  for (;;) {
    Sem_wait(&shared->budzik);

    shared->posilki = M;
    Sem_post(&shared->pelny);
    
    
    /* TODO Cook is asleep as long as there are meals.
     * If woken up they cook exactly M meals. */
  }
}

/* Do not bother cleaning up after this process. Let's assume that controlling
 * terminal sends SIGINT to the process group on CTRL+C. */
int main(void) {
  shared = Mmap(NULL, getpagesize(), PROT_READ|PROT_WRITE, MAP_ANON|MAP_SHARED,
                -1, 0);

  /* TODO: Initialize semaphores and other shared state. */
  Sem_init(&shared->przyGarnku, 1, 1);
  Sem_init(&shared->budzik, 1, 0);
  Sem_init(&shared->pelny, 1, 0);

  for (int i = 0; i < N; i++)
    if (Fork() == 0)
      savage();

  cook();

  return EXIT_SUCCESS;
}
