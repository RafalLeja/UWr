#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

#define PORT 7777
#define ADDR 0x7F000001
#define BUFFER_SIZE 65536
#define LISTEN_QUEUE 5

#define ERROR_MSG(str) perror(str)
#define CHECK(x, msg)                                                          \
  if ((x) < 0) {                                                               \
    ERROR_MSG(msg);                                                            \
    exit(EXIT_FAILURE);                                                        \
  }

void makeSocket(int *sockfd, struct sockaddr_in *servaddr);

void commHandler(int connfd);

void reverseString(char *input, char *output, int len);
