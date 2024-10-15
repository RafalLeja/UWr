#include "csapp.h"

static char buf[256];

#define LINE1 49
#define LINE2 33
#define LINE3 78

static void do_read(int fd) {
  /* TODO: Spawn a child. Read from the file descriptor in both parent and
   * child. Check how file cursor value has changed in both processes. */
  pid_t pid;
  pid = Fork();
  if (pid == 0){
    // Dziecko
    Read(fd, buf, 8);
    printf("%d> pozycja dziecka po przeczytaniu %ld\n", pid, Lseek(fd, 0, SEEK_CUR));
  } else {
    Read(fd, buf, 8);
    printf("%d> pozycja rodzica po przeczytaniu %ld\n", pid, Lseek(fd, 0, SEEK_CUR));
  }

  exit(0);
}

static void do_close(int fd) {
  /* TODO: In the child close file descriptor, in the parent wait for child to
   * die and check if the file descriptor is still accessible. */

  int status;
  pid_t pid;
  pid = Fork();
  if (pid == 0){
    // Dziecko
    printf("%d> dziecko zamyka plik %d\n", pid, fd);
    Close(fd);
    exit(0);
  } else {
    waitpid(pid, &status, 0);
    printf("%d> status dziecka = %d\n", pid, status);
    Read(fd, buf, LINE1);
    printf("%d> czytanie z pliku %d: %s\n", pid, fd, buf);
    exit(0);
  }

  exit(0);
}

int main(int argc, char **argv) {
  if (argc != 2)
    app_error("Usage: %s [read|close]", argv[0]);

  int fd = Open("test.txt", O_RDONLY, 0);

  if (!strcmp(argv[1], "read"))
    do_read(fd);
  if (!strcmp(argv[1], "close"))
    do_close(fd);
  app_error("Unknown variant '%s'", argv[1]);
}
