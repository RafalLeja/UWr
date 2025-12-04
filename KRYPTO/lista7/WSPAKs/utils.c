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

void commHandler(int connfd) {
  struct pollfd pfd;
  pfd.fd = connfd;

  pfd.events = POLLIN | POLLHUP;
  while (1) {
    int ready = poll(&pfd, 1, -1);
    if (ready == -1) {
      ERROR_MSG("Poll error");
      exit(EXIT_FAILURE);
    } else if (pfd.revents & POLLHUP) {
      printf("Client closed the connection\n");
      return;
    } else if ((pfd.revents & POLLIN) == 0) {

      continue;
    }

    char buffer[65535] = {0};
    char response[65535] = {0};
    int len;

    len = read(connfd, buffer, sizeof(buffer));
    if (len < 0) {
      ERROR_MSG("Read error");
      exit(EXIT_FAILURE);
    } else if (len == 0) {
      printf("Client closed the connection\n");
      return;
    }
    printf("Received message: %s\n", buffer);

    len -= 2; // \r\n
    if (len <= 0) {
      printf("Empty message, closing connection\n");
      return;
    }

    reverseString(buffer, response, len);

    write(connfd, response, len + 3);
  }
}

void reverseString(char *input, char *output, int len) {
  for (int i = 0; i <= len; i++) {
    output[i] = input[len - i];
  }
  output[len + 1] = '\r';
  output[len + 2] = '\n';
}
