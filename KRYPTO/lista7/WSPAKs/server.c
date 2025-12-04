#include "./server.h"
#include <arpa/inet.h>
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
#define KEYFILE "./keys/key.pem"
#define CERTFILE "./keys/cert.pem"
#define CAFILE "./ca_keys/ca_cert.pem"
// #define CRLFILE "crl.crl"

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
  CHECK(gnutls_certificate_set_x509_key_file(*x509_cred, CERTFILE, KEYFILE,
                                             GNUTLS_X509_FMT_PEM),
        "gnutls_certificate_set_x509_key_file failed");
}

int main() {
  signal(SIGINT, sigintHandler);
  signal(SIGCHLD, sigchldHandler);

  // TLS
  gnutls_certificate_credentials_t x509_cred;
  gnutls_priority_t priority_cache;
  gnutls_session_t session;

  printf("Initializing GnuTLS...\n");
  gnutlsInit(&x509_cred);
  gnutls_priority_init(&priority_cache, "NORMAL", NULL);
  gnutls_certificate_set_known_dh_params(x509_cred, GNUTLS_SEC_PARAM_NORMAL);
  printf("GnuTLS initialized\n");

  // normal
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
    CHECK(gnutls_init(&session, GNUTLS_SERVER), "gnutls_init failed");
    CHECK(gnutls_priority_set(session, priority_cache),
          "gnutls_set_priority failed");
    CHECK(gnutls_credentials_set(session, GNUTLS_CRD_CERTIFICATE, x509_cred),
          "gnutls_credentials_set failed");

    gnutls_certificate_server_set_request(session, GNUTLS_CERT_IGNORE);
    gnutls_handshake_set_timeout(session, GNUTLS_DEFAULT_HANDSHAKE_TIMEOUT);

    connfd = accept(sockfd, (struct sockaddr *)&cliaddr, &cliaddr_len);
    if (connfd < 0) {
      ERROR_MSG("Server accept failed");
      exit(EXIT_FAILURE);
    }

    char ipbuf[255] = {0};
    printf("- connection from %s, port %d\n",
           inet_ntop(AF_INET, &cliaddr.sin_addr, ipbuf, sizeof(ipbuf)),
           ntohs(cliaddr.sin_port));

    printf("Client connected\n");
    int pid = fork();
    if (pid == 0) {
      // Child
      close(sockfd);

      gnutls_transport_set_int(session, connfd);
      int ret;
      LOOP_CHECK(ret, gnutls_handshake(session));
      if (ret < 0) {
        fprintf(stderr, "*** Handshake failed: %s\n", gnutls_strerror(ret));
        gnutls_deinit(session);
        close(connfd);
        continue;
      }
      printf("- Handshake was completed\n");

      commHandler(session);
      printf("Client disconnected\n");

      LOOP_CHECK(ret, gnutls_bye(session, GNUTLS_SHUT_RDWR));
      close(connfd);
      gnutls_deinit(session);
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
  gnutls_certificate_free_credentials(x509_cred);
  gnutls_priority_deinit(priority_cache);
  gnutls_global_deinit();
  return 0;
}
