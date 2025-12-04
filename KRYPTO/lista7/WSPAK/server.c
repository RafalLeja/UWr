#include "./server.h"
#include <netinet/in.h>
#include <poll.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>

static int server_sockfd = -1;

void sigintHandler(int signum) {
  printf("\nCaught signal %d, exiting...\n", signum);
  if (server_sockfd != -1) {
    close(server_sockfd);
  }
  exit(EXIT_SUCCESS);
}

void sigchldHandler(int signum) {
  pid_t pid;
  int status;
  while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
    printf("Child process %d terminated\n", pid);
  }
}

int main() {
  signal(SIGINT, sigintHandler);
  signal(SIGCHLD, sigchldHandler);

  int sockfd, connfd;
  struct sockaddr_in servaddr = {0};
  struct sockaddr_in cliaddr = {0};
  socklen_t cliaddr_len = sizeof(cliaddr);

  makeSocket(&sockfd, &servaddr);
  server_sockfd = sockfd;

  if (listen(sockfd, 5) != 0) {
    ERROR_MSG("Listen failed");
    exit(EXIT_FAILURE);
  }
  while (1) {
    printf("Server listening on port %d\n", PORT);

    connfd = accept(sockfd, (struct sockaddr *)&cliaddr, &cliaddr_len);
    if (connfd < 0) {
      ERROR_MSG("Server accept failed");
      exit(EXIT_FAILURE);
    }

    printf("Client connected\n");
    int pid = fork();
    if (pid == 0) {
      // Child
      close(sockfd);
      commHandler(connfd);
      printf("Client disconnected\n");
      close(connfd);
      exit(0);
    } else if (pid > 0) {
      // Parent
      close(connfd);
    } else {
      ERROR_MSG("Fork failed");
      close(connfd);
    }
  }

  printf("Shutting down server\n");
  close(sockfd);
  return 0;
}
