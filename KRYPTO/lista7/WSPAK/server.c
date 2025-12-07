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

static int server_socket = -1;

void sigintHandler(int signum) {
  printf("\nCaught signal %d, exiting...\n", signum);
  if (server_socket != -1) {
    close(server_socket);
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

  int connection_socket;
  struct sockaddr_in server_addr = {0};
  struct sockaddr_in client_addr = {0};
  socklen_t client_addr_len = sizeof(client_addr);

  makeSocket(&server_socket, &server_addr);

  CHECK(listen(server_socket, LISTEN_QUEUE), "Listen failed");
  while (1) {
    printf("Server listening on port %d\n", PORT);

    connection_socket = accept(server_socket, (struct sockaddr *)&client_addr,
                               &client_addr_len);
    CHECK(connection_socket, "Server accept failed");

    printf("Client connected\n");
    int pid = fork();
    CHECK(pid, "Fork failed");

    if (pid == 0) {
      // Child
      close(server_socket);
      commHandler(connection_socket);
      printf("Client disconnected\n");
      close(connection_socket);
      exit(0);
    } else {
      // Parent
      close(connection_socket);
    }
  }

  printf("Shutting down server\n");
  close(server_socket);
  return 0;
}
