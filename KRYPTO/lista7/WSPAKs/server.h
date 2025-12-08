#include <errno.h>
#include <gnutls/gnutls.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

#define PORT 7777
#define ADDR 0x7F000001
#define MAX_BUF 65536
#define LISTEN_QUEUE 5

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

#define EINTR_WRAPPER(call)                                                    \
  ({                                                                           \
    int _result;                                                               \
    do {                                                                       \
      _result = (call);                                                        \
    } while (_result == -1 && errno == EINTR);                                 \
    _result;                                                                   \
  })

#define EINTR_WRAPPER_SSIZE(call)                                              \
  ({                                                                           \
    ssize_t _result;                                                           \
    do {                                                                       \
      _result = (call);                                                        \
    } while (_result == -1 && errno == EINTR);                                 \
    _result;                                                                   \
  })

void makeSocket(int *sockfd, struct sockaddr_in *servaddr);

void commHandler(gnutls_session_t session);

int ascii_check(char *input, int len);
void reverseString(char *input, char *output, int len);
