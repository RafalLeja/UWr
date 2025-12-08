#include "server.h"
#include <poll.h>
#include <stdio.h>
#include <unistd.h>

void makeSocket(int *sockfd, struct sockaddr_in *servaddr) {
  *sockfd = socket(AF_INET, SOCK_STREAM, 0);
  CHECK(*sockfd, "Socket creation failed");

  setsockopt(*sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));

  servaddr->sin_family = AF_INET;
  servaddr->sin_addr.s_addr = htonl(ADDR);
  servaddr->sin_port = htons(PORT);

  CHECK(bind(*sockfd, (struct sockaddr *)servaddr, sizeof(*servaddr)),
        "Socket bind failed");
}

void commHandler(int connfd) {
  struct pollfd pfd;
  pfd.fd = connfd;

  pfd.events = POLLIN | POLLHUP;
  while (1) {
    int ready = EINTR_WRAPPER(poll(&pfd, 1, -1));
    CHECK(ready, "Poll error");
    if (pfd.revents & POLLHUP) {
      printf("Client closed the connection\n");
      return;
    } else if ((pfd.revents & POLLIN) == 0) {

      continue;
    }

    char buffer[BUFFER_SIZE] = {0};
    char response[BUFFER_SIZE] = {0};
    int len;

    len = EINTR_WRAPPER_SSIZE(read(connfd, buffer, sizeof(buffer) - 1));
    CHECK(len, "Read error");
    if (len == 0) {
      printf("Client closed the connection\n");
      return;
    }
    printf("Received message: %s, of length %d\n", buffer, len);

    len -= 2; // \r\n
    if (len <= 0) {
      printf("Empty message, closing connection\n");
      return;
    }

    reverseString(buffer, response, len);

    ssize_t written = EINTR_WRAPPER_SSIZE(write(connfd, response, len + 2));
    CHECK(written, "Write error");
  }
}

void reverseString(char *input, char *output, int len) {
  for (int i = 0; i < len; i++) {
    output[i] = input[len - i - 1];
  }
  output[len] = '\r';
  output[len + 1] = '\n';
}
