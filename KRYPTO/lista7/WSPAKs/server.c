#include "./server.h"
#include <gnutls/gnutls.h>
#include <netinet/in.h>
#include <poll.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>

#define PORT 7777
#define ADDR 0x7F000001
#define KEYFILE "server.pem"
#define CERTFILE "cert.pem"
#define CAFILE "ca.crt"
#define CRLFILE "crl.crl"

#define ERROR_MSG(str) perror(str)
#define CHECK(x, msg)                                                          \
  if ((x) < 0) {                                                               \
    ERROR_MSG(msg);                                                            \
    exit(EXIT_FAILURE);                                                        \
  }

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

void gnutlsInit(gnutls_certificate_credentials_t *x509_cred) {
  CHECK(gnutls_global_init(), "gnutls_global_init failed");
  CHECK(gnutls_certificate_allocate_credentials(x509_cred),
        "gnutls_certificate_allocate_credentials failed");
  CHECK(gnutls_certificate_set_x509_trust_file(*x509_cred, CAFILE,
                                               GNUTLS_X509_FMT_PEM),
        "gnutls_certificate_set_x509_trust_file failed");
  CHECK(gnutls_certificate_set_x509_crl_file(*x509_cred, CRLFILE,
                                             GNUTLS_X509_FMT_PEM),
        "gnutls_certificate_set_x509_crl_file failed");
  CHECK(gnutls_certificate_set_x509_key_file(*x509_cred, CERTFILE, KEYFILE,
                                             GNUTLS_X509_FMT_PEM),
        "gnutls_certificate_set_x509_key_file failed");
}

int main() {
  signal(SIGINT, sigintHandler);
  signal(SIGCHLD, sigchldHandler);

  int sockfd, connfd;
  struct sockaddr_in servaddr = {0};
  struct sockaddr_in cliaddr = {0};

  makeSocket(&sockfd, &servaddr);
  server_sockfd = sockfd;

  if (listen(sockfd, 5) != 0) {
    ERROR_MSG("Listen failed");
    exit(EXIT_FAILURE);
  }
  while (1) {
    printf("Server listening on port %d\n", PORT);

    connfd = accept(sockfd, (struct sockaddr *)NULL, NULL);
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
