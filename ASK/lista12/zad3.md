```C
void foobar(long a[], size_t n, long y, long z) {
  for (int i = 0; i < n; i++) {
    long x = y - z;
    long j = 7 * i;
    a[i] = j + x * x;
  }
}

void foobar(long a[], size_t n, long y, long z) {
    long x = y - z;
    x *= x;
    for (int i = 0; i < n; i++) {
    a[i] = x;
    x += 7;
  }
}
```
### Niezmienniki: 
  - long x

### Zmienne indukcyjne:
  - int i
  - long j = 7 * i

### Które wyrażenia zostały wyniesione przed pętlę i dlaczego?
  - long x = y - z; ponieważ jest niezmiennikiem, a przez to niepotrzebnym kosztem

### Które wyrażenia uległy osłabieniu?
  - long j = 7 * i

## Definicje:

### Niezmiennik pętli
 - pojęcie używane w projektowaniu, analizie i dowodzeniu poprawności algorytmów.
 - Mówimy, że zdanie P jest niezmiennikiem pętli, jeżeli po każdym jej przebiegu jest ono prawdziwe.
 - W praktyce niezmiennik pętli traktowany jest jako założenie indukcyjne, na podstawie którego wykazuje się prawdziwość kroku indukcyjnego.

### Zmienne indukcyjna
  - zmienne które ulegają zmianie podczas przebiegu pętli

### Osłabianie
  - zamiana kosztownych operacji na równoważne oraz mniej kosztowne

