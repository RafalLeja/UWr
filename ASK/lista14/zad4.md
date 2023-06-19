__TLB jest w pełni asocjacyjne__ - składa się z jednego zbioru z wieloma liniami

__wtoczyć (ang. swap-in)__ - wczytać stronę/ramkę z dysku do pamięci głównej

__ofiara__ - usuwana strona pamięci, jeśli zabraknie miejsca, a trzeba wczytać nową stronę

__ramka__ - odpowiednik strony w fizycznej przestrzeni adresowej

__błąd strony__ - występuje, jeśli pytamy o stronę, która ni jest załadowana do pamięci głównej

Strona ma $2^{12}$ bajtów czyli potrzebujemy 12 bitów na VPO
Adres wirtualny: (TLBT, VPO) = (addr15…12, addr11…0)

### 0x123d

Binarnie: 0001 0010 0011 1101

TLBT: 1

__Page fault__

| VPN | Valid | PPN  |
| ----| ----- | ---- |
| 00  |   1   |  05  |
| 01  |   1   |  0d  |
| 02  |   0   | dysk |
| 03  |   1   |  06  |
| 04  |   1   |  09  |
| 05  |   1   |  0b  |
| 06  |   0   | dysk |
| 07  |   1   |  04  |
| 08  |   0   | dysk |
| 09  |   0   | dysk |
| 0a  |   1   |  03  |
| 0b  |   1   |  0c  |
| 0c  |   0   | brak |

| Valid | Tag | LRU | PPN |
| ----- | --- | --- | --- |
|   1   | 0B  | 1   | 0c  |
|   1   | 07  | 2   | 04  |
|   1   | 03  | 3   | 06  |
|   1   | 01  | 0   | 0d  |

### 0x08b3

Binarnie: 0000 1000 1011 0011
TLBT: 0

__Page hit__

| Valid | Tag | LRU | PPN |
| ----- | --- | --- | --- |
|   1   | 0B  | 2   | 0c  |
|   1   | 07  | 3   | 04  |
|   1   | 00  | 0   | 05  |
|   1   | 01  | 1   | 0d  |

### 0x365c

Binarnie: 0011 0110 0101 1100
TLBT: 3

__Page hit__

| Valid | Tag | LRU | PPN |
| ----- | --- | --- | --- |
|   1   | 0B  | 3   | 0c  |
|   1   | 03  | 0   | 06  |
|   1   | 00  | 1   | 05  |
|   1   | 01  | 2   | 0d  |

### 0x871b

Binarnie: 1000 0111 0001 1011
TLBT: 8

__Page fault__

| VPN | Valid | PPN  |
| ---:| ----- | ---- |
| 00  |   1   |  05  |
| 01  |   1   |  0d  |
| 02  |   0   | dysk |
| 03  |   1   |  06  |
| 04  |   1   |  09  |
| 05  |   1   |  0b  |
| 06  |   0   | dysk |
| 07  |   1   |  04  |
| 08  |   0   |  0e  |
| 09  |   0   | dysk |
| 0a  |   1   |  03  |
| 0b  |   1   |  0c  |
| 0c  |   0   | brak |

| Valid | Tag | LRU | PPN |
| ----- | --- | --- | --- |
|   1   | 08  | 0   | 0e  |
|   1   | 03  | 1   | 06  |
|   1   | 00  | 2   | 05  |
|   1   | 01  | 3   | 0d  |

### 0xbee6

Binarnie: 1011 1110 1110 0110
TLBT: b

__Page hit__

| Valid | Tag | LRU | PPN |
| ----- | --- | --- | --- |
|   1   | 08  | 1   | 0e  |
|   1   | 03  | 2   | 06  |
|   1   | 00  | 3   | 05  |
|   1   | 0b  | 0   | 0c  |

### 0x3140

Binarnie: 0011 0001 0100 0000
TLBT: 3

__TLB hit__

| Valid | Tag | LRU | PPN |
| ----- | --- | --- | --- |
|   1   | 08  | 2   | 0e  |
|   1   | 03  | 0   | 06  |
|   1   | 00  | 3   | 05  |
|   1   | 0b  | 1   | 0c  |

### 0xc049

Binarnie: 1100 0000 0100 1001
TLBT: C

__Page fault - segfault__