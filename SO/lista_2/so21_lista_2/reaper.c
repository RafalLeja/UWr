#include "csapp.h"

static pid_t spawn(void (*fn)(void)) {
  pid_t pid = Fork();
  if (pid == 0) {
    fn();
    printf("(%d) I'm done!\n", getpid());
    exit(EXIT_SUCCESS);
  }
  return pid;
}

static void grandchild(void) {
  printf("(%d) Waiting for signal!\n", getpid());
  pause();
  printf("(%d) Got the signal!\n", getpid());
}

static void child(void) {
  pid_t pid;
  pid = spawn(grandchild);
  printf("(%d) Grandchild (%d) spawned!\n", getpid(), pid);
  setpgid(pid, getpid());
}

/* Runs command "ps -o pid,ppid,pgrp,stat,cmd" using execve(2). */
static void ps(void) {
  pid_t pid = Fork();
  if (pid == 0) {
    char *argv[] = {"/bin/ps", "-o", "pid,ppid,pgrp,stat,cmd", NULL};
    execve("/bin/ps", argv, environ);
    exit(EXIT_SUCCESS);
  }
  waitpid(pid, NULL, 0);
}

int main(void) {
#ifdef LINUX
  Prctl(PR_SET_CHILD_SUBREAPER, 1);
#endif
  printf("(%d) I'm a reaper now!\n", getpid());

  // pid_t pid, pgrp;
  int status;
  // pgrp = getpgrp();

  pid_t pid = spawn(child);
  setpgid(pid, 0);
  waitpid(-pid, &status, 0);
  ps();

  Kill(-pid, SIGINT);
  waitpid(-pid, &status, 0);

  return EXIT_SUCCESS;
}
