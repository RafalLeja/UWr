#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>

#define PORT 7777
#define ADDR 0x7F000001
#define ERROR_MSG(str) perror(str)

void makeSocket(int *sockfd, struct sockaddr_in *servaddr);

void commHandler(int connfd);

void reverseString(char *input, char *output, int len);
