#include <gnutls/gnutls.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>

#define PORT 7777
#define ADDR 0x7F000001
#define ERROR_MSG(str) perror(str)
#define MAX_BUF 65535

#define ERROR_MSG(str) perror(str)
#define CHECK(x, msg)                                                          \
  if ((x) < 0) {                                                               \
    ERROR_MSG(msg);                                                            \
    exit(EXIT_FAILURE);                                                        \
  }
#define LOOP_CHECK(rval, cmd)                                                  \
  do {                                                                         \
    rval = cmd;                                                                \
  } while (rval == GNUTLS_E_AGAIN || rval == GNUTLS_E_INTERRUPTED)

void makeSocket(int *sockfd, struct sockaddr_in *servaddr);

void commHandler(gnutls_session_t session);

void reverseString(char *input, char *output, int len);
