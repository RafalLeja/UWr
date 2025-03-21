// Rafał Leja 340879

#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <poll.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

#define N_PACKETS 3

// globalny licznik sekwencji
static int seq = 0;

// struktura do przechowywania informacji o pakietach które wysłaliśmy
// i otrzymaliśmy
struct packet_info {
  long send_time;
  long recv_time;
  int seq;
  char ip[20];
} packet_info;

// struktura do przechowywania informacji o źródłach pakietów
struct source_info {
  char ip[20];
  long sum;
  int cnt;
} source_info;

// funkcje z wykładu
// ------------------
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
// ------------------

// funkcja dodająca źródło na podstawie odebranego pakietu
int addToSrc(struct source_info *srcs, int n, struct packet_info packet) {
  for (int i = 0; i < n; i++) {
    // zapisz wolne miejsce w tablicy
    if (srcs[i].cnt == 0) {
      strcpy(srcs[i].ip, packet.ip);
    }
    // odnaleziono źródło, zaktualizuj dane
    if (strcmp(srcs[i].ip, packet.ip) == 0) {
      srcs[i].sum += packet.recv_time - packet.send_time;
      srcs[i].cnt++;
      return n;
    }
  }

  // nie znaleziono źródła, i nie ma miejsca w tablicy
  // hopefully unreachable
  return -1;
}

// funkcja wysyłająca pakiet
void sendPacket(char *destination, int ttl, struct packet_info *packet_info) {
  // otwieranie gniazda i ustawianie TTL
  int sock_fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
  if (sock_fd < 0 ||
      setsockopt(sock_fd, IPPROTO_IP, IP_TTL, &ttl, sizeof(int)) < 0) {
    ERROR("socket error");
  }

  // struktura adresowa
  struct sockaddr_in recipient;
  memset (&recipient, 0, sizeof(recipient));
  recipient.sin_family = AF_INET;
  inet_pton (AF_INET, destination, &recipient.sin_addr);

  // struktura nagłówka ICMP
  struct icmp header;
  header.icmp_type = ICMP_ECHO;
  header.icmp_code = 0;
  header.icmp_hun.ih_idseq.icd_id = getpid() & 0xFFFF;
  // zapisujemy seq w strukturach i zwiekszamy globalny licznik
  packet_info->seq = seq;
  header.icmp_hun.ih_idseq.icd_seq = seq++;
  header.icmp_cksum = 0;
  header.icmp_cksum =
      compute_icmp_checksum((u_int16_t *)&header, sizeof(struct icmphdr));

  // mierzymy czas wysłania pakietu
  struct timespec send_time;
  clock_gettime(CLOCK_MONOTONIC_RAW, &send_time);

  // wysyłanie pakietu
  ssize_t bytes_sent = sendto(sock_fd, &header, sizeof(struct icmphdr), 0,
                              (struct sockaddr *)&recipient, sizeof(recipient));

  // zapisujemy czas wysłania pakietu
  packet_info->send_time = send_time.tv_nsec / 1000000;

  // obsługa błędów
  if (bytes_sent < 0) {
    ERROR("sendto error");
  }

  // zamknięcie gniazda
  close(sock_fd);
}


// funkcja odbierająca pakiety
void recvPackets(struct packet_info *packets) {
  // otwieranie gniazda
  int sock_fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
  if (sock_fd < 0) {
    ERROR("socket error");
  }
  
  struct pollfd fds;
  fds.fd = sock_fd;
  fds.events = POLLIN;

  int count = 0;

  for (int i = 0; i < 3; i++) {
    int ret = poll(&fds, 1, 1000);

    struct timespec end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);

    if (ret < 0) {
      ERROR("poll error");
    } else if (ret == 0) {
      break;
    } else if (!(fds.revents & POLLIN)) {
      continue;
    }

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

    char sender_ip_str[20];
    inet_ntop(AF_INET, &(sender.sin_addr), sender_ip_str,
              sizeof(sender_ip_str));

    struct iphdr *ip_header = (struct iphdr *)buffer;
    int ip_header_len = 4 * (ip_header->ihl);

    struct icmphdr *icmp_header = (struct icmphdr *)(buffer + ip_header_len);

    if (icmp_header->type != ICMP_TIME_EXCEEDED) {
      // found recipient!

      u_int16_t id = icmp_header->un.echo.id;
      u_int16_t seq = icmp_header->un.echo.sequence;

      for (int i = 0; i < 3; i++) {
        if (seq == packets[i].seq && id == getpid() && 0xFFFF) {
          strcpy(packets[i].ip, sender_ip_str);
          packets[i].recv_time = end.tv_nsec / 1000000;
          count++;
          break;
        }
      }

    } else {
      // TTL exceeded
      struct iphdr *ip_header2 =
          (struct iphdr *)(buffer + ip_header_len + sizeof(struct icmphdr));
      int ip_header_len2 = 4 * (ip_header2->ihl);

      struct icmphdr *icmp_header2 =
          (struct icmphdr *)(buffer + ip_header_len + sizeof(struct icmphdr) +
                             ip_header_len2);

      u_int16_t id = icmp_header2->un.echo.id;
      u_int16_t seq = icmp_header2->un.echo.sequence;

      for (int i = 0; i < 3; i++) {
        if (seq == packets[i].seq && id == getpid() && 0xFFFF) {
          strcpy(packets[i].ip, sender_ip_str);
          packets[i].recv_time = end.tv_nsec / 1000000;
          count++;
          break;
        }
      }
    }

    if (count == 3) {
      break;
    }
  }

  close(sock_fd);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s <hostname>\n", argv[0]);
    exit(1);
  }

  if (inet_aton(argv[1], NULL) == 0) {
    printf("Invalid hostname, use numbers\n");
    exit(1);
  }

  for (int i = 1; i <= 30; i++) {
    struct packet_info packets[N_PACKETS];
    memset(packets, 0, sizeof(packets));
    struct source_info srcs[N_PACKETS];
    memset(srcs, 0, sizeof(srcs));

    for (int k = 0; k < N_PACKETS; k++) {
      sendPacket(argv[1], i, &packets[k]);
    }

    recvPackets(packets);

    for (int k = 0; k < N_PACKETS; k++) {
      addToSrc(srcs, N_PACKETS, packets[k]);
    }

    char ips[20 * N_PACKETS] = {0};
    long sum = 0;
    int cnt = 0;
    int blanks = 0;
    for (int k = 0; k < N_PACKETS; k++) {
      if (srcs[k].cnt == 0) {
        break;
      }
      if (srcs[k].ip[0] == '\0') {
        blanks += 1;
        continue;
      }

      strcat(ips, srcs[k].ip);
      strcat(ips, " ");
      sum += srcs[k].sum;
      cnt += 1;
    }

    if (blanks == N_PACKETS) {
      printf("%d. *\n", i);
    } else if (blanks > 0) {
      printf("%d. %s\t???\n", i, ips);
    } else {
      printf("%d. %s\t%ldms\n", i, ips, sum / cnt);
    }

    if (strcmp(srcs[0].ip, argv[1]) == 0) {
      break;
    }
  }

  return 0;
}
