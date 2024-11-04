### Zapoznaj się z krytyką interfejsu plików przedstawioną w podrozdziale „ioctl and fcntl Are an Embarrassment”. Do czego służy wywołanie systemowe ioctl(2)?
ioctl służy do modyfikacji parametrów plików specjalnych, takich jak urządzenia znakowe i blokowe, rury.
### Zauważ, że stosowane jest głównie do plików urządzeń znakowych lub blokowych. Na podstawie pliku ioccom.h2 wyjaśnij znaczenie drugiego i trzeciego parametru wywołania ioctl.
```
* Ioctl's have the command encoded in the lower word, and the size of
any in or out parameters in the upper word.  The high 3 bits of the
upper word are used to encode the in/out status of the parameter.

31  29 28                     16 15            8 7              0
+---------------------------------------------------------------+
| I/O | Parameter Length        | Command Group | Command       |
+---------------------------------------------------------------+
```

trzeci parametr to wskaźnik do struktury, która zawiera dane do przekazania do urządzenia

### Używając przeglądarki kodu jądra NetBSD znajdź definicje operacji «DIOCEJECT», «KIOCTYPE» i «SIOCGIFCONF», a następnie wytłumacz co one robią.

```C
#define DIOCEJECT	_IOW('d', 112, int)	/* eject removable disk */
#define	KIOCTYPE	_IOR('k', 9, int)	/* get keyboard type */
#define	SIOCGIFCONF	_IOWR('i', 38, struct ifconf)	/* get ifnet list */
SIOCGIFCONF
Return a list of interface (transport layer) addresses. This currently means only addresses of the AF_INET (IPv4) family for compatibility. The user passes a ifconf structure as argument to the ioctl. It contains a pointer to an array of ifreq structures in ifc_req and its length in bytes in ifc_len. The kernel fills the ifreqs with all current L3 interface addresses that are running: ifr_name contains the interface name (eth0:1 etc.), ifr_addr the address. The kernel returns with the actual length in ifc_len. If ifc_len is equal to the original length the buffer probably has overflowed and you should retry with a bigger buffer to get all addresses. When no error occurs the ioctl returns 0; otherwise -1. Overflow is not an error.
```