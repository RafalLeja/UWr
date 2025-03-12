// Rafał Leja 06.03.2025

#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>
#include <stddef.h>

struct packet_info {
  struct timespec send_time;
  struct timespec recv_time;
  int seq;
  char ip[20];
} packet_info;

void ERROR(const char *str) {
  fprintf(stderr, "%s: %s\n", str, strerror(errno));
  exit(EXIT_FAILURE);
}

void print_as_bytes(unsigned char *buff, ssize_t length) {
  for (ssize_t i = 0; i < length; i++, buff++)
    printf("%.2x ", *buff);
}

u_int16_t compute_icmp_checksum(const void *buff, int length) {
  const u_int16_t *ptr = buff;
  u_int32_t sum = 0;
  assert(length % 2 == 0);
  for (; length > 0; length -= 2)
    sum += *ptr++;
  sum = (sum >> 16U) + (sum & 0xffffU);
  return (u_int16_t)(~(sum + (sum >> 16U)));
}

void sendPacket(char *destination, int ttl, struct packet_info *packet_info) {
  int sock_fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
  if (sock_fd < 0 ||
      setsockopt(sock_fd, IPPROTO_IP, IP_TTL, &ttl, sizeof(int)) < 0)
    fprintf(stderr, "socket error\n"), exit(1);

  struct sockaddr_in target;
  memset(&target, 0, sizeof(struct sockaddr_in));
  target.sin_family = AF_INET;
  target.sin_addr.s_addr = inet_addr(destination);

  int seq = rand() % 0xFFFF;
  packet_info->seq = seq;

  struct icmp header;
  header.icmp_type = ICMP_ECHO;
  header.icmp_code = 0;
  header.icmp_hun.ih_idseq.icd_id = getpid() & 0xFFFF;
  header.icmp_hun.ih_idseq.icd_seq = seq;
  header.icmp_cksum = 0;
  header.icmp_cksum =
      compute_icmp_checksum((u_int16_t *)&header, sizeof(struct icmphdr));

  clock_gettime(CLOCK_MONOTONIC_RAW, &packet_info->send_time);
  // time_t send_time = time(NULL);
  // packet_info->send_time = send_time;

  ssize_t bytes_sent = sendto(sock_fd, &header, sizeof(struct icmphdr), 0,
                              (struct sockaddr *)&target, sizeof(target));

  if (bytes_sent < 0) {
    fprintf(stderr, "sendto error\n");
    exit(1);
  }

  close(sock_fd);
}

void recvPackets(struct packet_info *packets) {
  int sock_fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
  if (sock_fd < 0)
    ERROR("socket error");

  int count = 0;
  time_t start = time(NULL);

  while (time(NULL) - start < 1) {
  
    struct sockaddr_in sender;
    socklen_t sender_len = sizeof(sender);
    u_int8_t buffer[IP_MAXPACKET];

    ssize_t packet_len = recvfrom(sock_fd, buffer, IP_MAXPACKET, MSG_DONTWAIT,
                                  (struct sockaddr *)&sender, &sender_len);
    if (packet_len < 0) {
      if (errno == EWOULDBLOCK) {
        continue;
      }
      ERROR("recvfrom error");
    }

    struct timespec end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);

    char sender_ip_str[20];
    inet_ntop(AF_INET, &(sender.sin_addr), sender_ip_str,
              sizeof(sender_ip_str));

    struct iphdr *ip_header = (struct iphdr *)buffer;
    int ip_header_len = 4 * (ip_header->ihl);

    struct icmphdr *icmp_header = (struct icmphdr *)(buffer + ip_header_len);
    ssize_t header_len = packet_len - ip_header_len;

    struct iphdr *ip_header2 = (struct iphdr *)(buffer + ip_header_len + sizeof(struct icmphdr));
    int ip_header_len2 = 4 * (ip_header2->ihl);

    struct icmphdr *icmp_header2 = (struct icmphdr *)(buffer + ip_header_len + sizeof(struct icmphdr) + ip_header_len2);

    u_int16_t id = icmp_header2->un.echo.id;
    u_int16_t seq = icmp_header2->un.echo.sequence;

    for (int i = 0; i < 3; i++) {
      if (seq == packets[i].seq &&
          id == getpid() && 0xFFFF) {
        strcpy(packets[i].ip, sender_ip_str);
        packets[i].recv_time = end;
        count++;
        // printf("found %d packet\n", i);
        break;
      }
    }

    if (count == 3) {
      break;
    }
  }

  close(sock_fd);
}

int main(int argc, char *argv[]) {
  srand(time(NULL) ^ getpid());

  if (argc != 2) {
    printf("Usage: %s <hostname>\n", argv[0]);
    exit(1);
  }

  printf("Traceroute to %s\n", argv[1]);

  for (int i = 1; i <= 14; i++) {
    struct packet_info packets[3];

    for (int k = 0; k < 3; k++) {
      sendPacket(argv[1], i, &packets[k]);
    }

    recvPackets(packets);

    for (int k = 0; k <3; k++) {
      if (packets[k].recv_time.tv_nsec != 0) {
        printf("%d. %s %ldms\n", i, packets[k].ip,
               (packets[k].recv_time.tv_nsec - packets[k].send_time.tv_nsec) / 1000000);
      } else {
        printf("%d. *\n", i);
      }
    }
    // sleep(1);

    if (strcmp(packets[0].ip, argv[1]) == 0 &&
        strcmp(packets[1].ip, argv[1]) == 0 &&
        strcmp(packets[2].ip, argv[1]) == 0) {
      break;
    }
  }

  return 0;
}
