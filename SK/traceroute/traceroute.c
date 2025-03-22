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

#define DEBUG 0

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
  if (strlen(packet.ip) == 0) {
    // nie ma adresu IP
    return -1;
  }

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
  memset(&recipient, 0, sizeof(recipient));
  recipient.sin_family = AF_INET;
  inet_pton(AF_INET, destination, &recipient.sin_addr);

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
  clock_gettime(CLOCK_MONOTONIC, &send_time);

  // wysyłanie pakietu
  ssize_t bytes_sent = sendto(sock_fd, &header, sizeof(struct icmphdr), 0,
                              (struct sockaddr *)&recipient, sizeof(recipient));

  // zapisujemy czas wysłania pakietu
  packet_info->send_time = send_time.tv_nsec / 1000;

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

  // struktura do poll()
  struct pollfd fds;
  fds.fd = sock_fd;
  fds.events = POLLIN;

  // powtarzamy aż nie otrzymamy wszystkich pakietów
  struct timespec end;
  int count = 0;
  while (count < N_PACKETS) {
    // czekamy na pakiet przez max 1s
    int ret = poll(&fds, 1, 1000);

    // zapisujemy czas otrzymania pakietu
    clock_gettime(CLOCK_MONOTONIC, &end);

    if (ret < 0) {
      ERROR("poll error");
    } else if (ret == 0) {
      // timeout
      break;
    } else if (!(fds.revents & POLLIN)) {
      // gniazdo niegotowe
      continue;
    }

    // odbieranie pakietu
    struct sockaddr_in sender;
    socklen_t sender_len = sizeof(sender);
    u_int8_t buffer[IP_MAXPACKET];

    ssize_t packet_len = recvfrom(sock_fd, buffer, IP_MAXPACKET, 0,
                                  (struct sockaddr *)&sender, &sender_len);
    if (packet_len < 0) {
      ERROR("recvfrom error");
    }

    // zapisujemy adres IP nadawcy
    char sender_ip_str[20];
    inet_ntop(AF_INET, &(sender.sin_addr), sender_ip_str,
              sizeof(sender_ip_str));

    // parsujemy nagłówek IP i ICMP
    struct iphdr *ip_header = (struct iphdr *)buffer;
    int ip_header_len = 4 * (ip_header->ihl);
    struct icmphdr *icmp_header = (struct icmphdr *)(buffer + ip_header_len);

    u_int16_t id;
    u_int16_t seq;

    // sprawdzamy typ pakietu
    if (icmp_header->type == ICMP_ECHOREPLY) {
      // echo reply
      id = icmp_header->un.echo.id;
      seq = icmp_header->un.echo.sequence;

    } else if (icmp_header->type == ICMP_TIME_EXCEEDED) {
      // TTL exceeded

      // musimy odczytać nagłówek IP i ICMP z pakietu wewnętrznego
      struct iphdr *inner_ip_header = (struct iphdr *)(icmp_header + 1);
      int inner_ip_header_len = 4 * (inner_ip_header->ihl);

      struct icmphdr *inner_icmp_header =
          (struct icmphdr *)((u_int8_t *)inner_ip_header + inner_ip_header_len);

      id = inner_icmp_header->un.echo.id;
      seq = inner_icmp_header->un.echo.sequence;
    }

    // szukamy pakietu w tablicy i zapisujemy dane
    for (int i = 0; i < N_PACKETS; i++) {
      if (seq == packets[i].seq && id == getpid() && 0xFFFF) {
        strcpy(packets[i].ip, sender_ip_str);
        packets[i].recv_time = end.tv_nsec / 1000;
        count++;
        break;
      }
    }
  }

  // zamykamy gniazdo
  close(sock_fd);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    // zła ilość argumentów
    ERROR("Usage: ./traceroute <hostname>");
  }

  if (inet_aton(argv[1], NULL) == 0) {
    // niepoprawny adres IP
    ERROR("Invalid IP address");
  }

  printf("traceroute to %s\n", argv[1]);

  // wysyłamy pakiety z TTL od 1 do 30
  for (int i = 1; i <= 30; i++) {
    // tablice do przechowywania informacji o pakietach i źródłach
    struct packet_info packets[N_PACKETS] = {0};
    struct source_info srcs[N_PACKETS] = {0};

    // wysyłamy pakiety
    for (int k = 0; k < N_PACKETS; k++) {
      sendPacket(argv[1], i, &packets[k]);
    }

    // odbieramy pakiety
    recvPackets(packets);

    // zliczamy źródła pakietów
    for (int k = 0; k < N_PACKETS; k++) {
      addToSrc(srcs, N_PACKETS, packets[k]);
    }

    // przygotowujemy dane do wypisania
    char ips[20 * N_PACKETS] = {0};
    long sum = 0;
    int cnt = 0;
    for (int k = 0; k < N_PACKETS; k++) {
      if (srcs[k].cnt == 0) {
        break;
      }

      strcat(ips, srcs[k].ip);
      strcat(ips, " ");
      sum += srcs[k].sum;
      cnt += srcs[k].cnt;
    }

    if (DEBUG) {
      printf("TTL: %d\n", i);
      printf("IPs: %s\n", ips);
      printf("Sum: %ld\n", sum);
      printf("Cnt: %d\n", cnt);
    }

    if (cnt == 0) {
      printf("%d *\n", i);
    } else if (cnt < N_PACKETS) {
      printf("%d %s\t???\n", i, ips);
    } else {
      printf("%d %s\t%.3gms\n", i, ips, (double)sum / (cnt * 1000));
    }

    if (strcmp(srcs[0].ip, argv[1]) == 0) {
      break;
    }
  }

  return 0;
}
