#include "server.h"
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void makeSocket(int *sockfd, struct sockaddr_in *servaddr) {
  *sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (*sockfd == -1) {
    ERROR_MSG("Socket creation failed");
    exit(EXIT_FAILURE);
  }

  setsockopt(*sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));

  servaddr->sin_family = AF_INET;
  servaddr->sin_addr.s_addr = htonl(ADDR);
  servaddr->sin_port = htons(PORT);

  if (bind(*sockfd, (struct sockaddr *)servaddr, sizeof(*servaddr)) != 0) {
    ERROR_MSG("Socket bind failed");
    exit(EXIT_FAILURE);
  }
}

void commHandler(gnutls_session_t session) {
  while (1) {
    char buffer[MAX_BUF] = {0};
    char response[MAX_BUF] = {0};
    int ret;
    LOOP_CHECK(ret, gnutls_record_recv(session, buffer, MAX_BUF));
    if (ret == 0) {
      printf("Client closed the connection\n");
      break;
    } else if (ret < 0 && gnutls_error_is_fatal(ret)) {
      fprintf(stderr, "*** Error in record recv: %s\n", gnutls_strerror(ret));
      break;
    } else if (ret < 0) {
      printf("Recieved corrupted data: %d, closing connection\n", ret);
      break;
    }

    ret -= 2; // \r\n
    if (ret <= 0) {
      printf("Empty message, closing connection\n");
      break;
    }

    reverseString(buffer, response, ret);

    CHECK(gnutls_record_send(session, response, ret + 3),
          "Error in record send");
  }
}

void reverseString(char *input, char *output, int len) {
  for (int i = 0; i <= len; i++) {
    output[i] = input[len - i];
  }
  output[len + 1] = '\r';
  output[len + 2] = '\n';
}
