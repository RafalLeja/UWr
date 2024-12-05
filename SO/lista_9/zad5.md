## Przyjrzyjmy się warunkom brzegowym, które występują w trakcie używania interfejsu gniazd BSD. Kiedy read(2) i write(2) na gniazdach strumieniowych zwracają short counts?

- write/send (man 2 send):
    - jeśli wiadomość jest za długa 
        - ```If the message is too long to pass atomically through the underlying protocol, the error EMSGSIZE is returned, and the message is not transmitted.```
    - jeśli wiadomoć nie mieści się w buforze
        - ```When  the  message  does not fit into the send buffer of the socket, send() normally blocks, unless the socket has been placed in nonblocking I/O mode.  In nonblocking mode it would fail with the error EAGAIN  or  EWOULD‐BLOCK in this case.  The select(2) call may be used to determine when it is possible to send more data.```

- read/recv (man 2 recv):
    - jeśli przesłano mniej danych
        - ``` The receive calls normally return any data available, up to the  requested  amount, rather than waiting for receipt of the full amount requested.```


## Skąd wiemy, że odebrany datagram UDP nie został obcięty przez jądro w trakcie kopiowania do przestrzeni użytkownika?

Możemy sprawdzić długość datagramu, którą zwraca recvfrom i porównać z nagłówkiem IP, który zawiera długość całego pakietu

## Z jakich przyczyn należy być przygotowanym na to, że operacje na gniazdach zwrócą «EINTR»?

Gdy proces otrzyma sygnał, a był w trakcie funkcji read/write, to funkcja ta zostanie przerwana i zwróci EINTR
Możemy wtedy ponowić operację

## Co się stanie, jeśli klient spróbuje zapisać do gniazda powiązanego z połączeniem, które serwer zdążył już zamknąć?

jeśli serwer zamknął gniazdo, a klient spróbuje pisać do niego, to zostanie zwrócony błąd

```plaintext
EPIPE  The  local end has been shut down on a connection oriented socket.  In this case, the process will also
        receive a SIGPIPE unless MSG_NOSIGNAL is set.
```

## Dlaczego w kodzie funkcji «open_listenfd» użyto wywołania setsockopt(2) z opcją «SO_REUSEADDR» [3, 61.10]?

Jesli port jest zajęty to setsockopt pozwala na ponowne użycie portu

```C
int open_listenfd(char *port) 
{
    struct addrinfo hints, *listp, *p;
    int listenfd, rc, optval=1;

    /* Get a list of potential server addresses */
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM;             /* Accept connections */
    hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG; /* ... on any IP address */
    hints.ai_flags |= AI_NUMERICSERV;            /* ... using port number */
    if ((rc = getaddrinfo(NULL, port, &hints, &listp)) != 0) {
        fprintf(stderr, "getaddrinfo failed (port %s): %s\n", port, gai_strerror(rc));
        return -2;
    }

    /* Walk the list for one that we can bind to */
    for (p = listp; p; p = p->ai_next) {
        /* Create a socket descriptor */
        if ((listenfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0) 
            continue;  /* Socket failed, try the next */

        /* Eliminates "Address already in use" error from bind */
        setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR,    //line:netp:csapp:setsockopt
                   (const void *)&optval , sizeof(int));

        /* Bind the descriptor to the address */
        if (bind(listenfd, p->ai_addr, p->ai_addrlen) == 0)
            break; /* Success */
        if (close(listenfd) < 0) { /* Bind failed, try the next */
            fprintf(stderr, "open_listenfd close failed: %s\n", strerror(errno));
            return -1;
        }
    }


    /* Clean up */
    freeaddrinfo(listp);
    if (!p) /* No address worked */
        return -1;

    /* Make it a listening socket ready to accept connection requests */
    if (listen(listenfd, LISTENQ) < 0) {
        close(listenfd);
	return -1;
    }
    return listenfd;
}
```

## Co by się stało gdyby programista o tym zapomniał?

Jeśli programista zapomni o tym, to jeśli port jest zajęty to bind zwróci błąd

```plaintext
EADDRINUSE
      The given address is already in use.  This usually occurs when another program is already using the port you are trying to use.
```