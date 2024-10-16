#include "csapp.h"

static void signal_handler(int signum, siginfo_t *info, void *data) {
  if (signum == SIGINT) {
    safe_printf("(%d) Screw you guys... I'm going home!\n", getpid());
    _exit(0);
  }
}

static void play(pid_t next, const sigset_t *set) {
  for (;;) {
    printf("(%d) Waiting for a ball!\n", getpid());
    Sigsuspend(set);
    usleep((300 + random() % 400) * 1000);
    Kill(next, SIGUSR1);
    printf("(%d) Passing ball to (%d)!\n", getpid(), next);
  }
}

int main(int argc, char *argv[]) {
  if (argc != 2)
    app_error("Usage: %s [CHILDREN]", argv[0]);

  int children = atoi(argv[1]);

  if (children < 4 || children > 20)
    app_error("Give number of children in range from 4 to 20!");

  /* Register signal handler for SIGUSR1 */
  struct sigaction action = {.sa_sigaction = signal_handler};
  Sigaction(SIGINT, &action, NULL);
  Sigaction(SIGUSR1, &action, NULL);

  pid_t pids[21];
  for (int i = children -1 ; i >= 0; i--)
  {
    pid_t pid = Fork();
    if(pid == 0){
      sigset_t set;
      Sigprocmask(0, NULL, &set);
      play(pids[i+1], &set);
    }
    pids[i] = pid;
  }
  pids[children] = getpid();
  printf("podaje do %d\n", pids[0]);
  Kill(pids[0], SIGUSR1);
  sigset_t rootSet;
  Sigprocmask(0, NULL, &rootSet);
  play(pids[0], &rootSet);
  
  /* TODO: Start all processes and make them wait for the ball! */

  return EXIT_SUCCESS;
}
