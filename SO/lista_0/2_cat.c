#include "apue.h"
#include <fcntl.h>

#define BUFFSIZE 4096

// int main(void) {
//   int n;
//   char buf[BUFFSIZE];

//   while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
//     if (write(STDOUT_FILENO, buf, n) != n)
//       err_sys("write error");

//   if (n < 0)
//     err_sys("read error");

//   exit(0);
// }

//----------------

int main(int argc, char *argv[]) {
  int n;
  char buf[BUFFSIZE];


  int desc = open(argv[1], O_CREAT | O_RDWR, FILE_MODE);

  while ((n = read(desc, buf, BUFFSIZE)) > 0)
    if (write(STDOUT_FILENO, buf, n) != n)
      err_sys("write error");

  if (n < 0)
    err_sys("read error");

  exit(0);
}
