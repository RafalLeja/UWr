```C
long decode(long x, long y) {
    return ((x + y) ^ x ^ y) & (x * y >> 63);
}
```

Wykorzystuje ona właściwości bitowe operacji XOR i AND do uzyskania takiego samego wyniku jak w oryginalnym kodzie asemblerowym. W linii 1 dodajemy argumenty «x» i «y», a w linii 2 i 3 wykonujemy operacje XOR na wyniku dodawania i na argumentach «x» i «y». W linii 5 obliczamy wartość «x*y» i przesuwamy ją o 63 bity w prawo, a następnie wykonujemy operację AND z wynikiem operacji XOR. W ten sposób otrzymujemy taki sam wynik jak w linii 5 oryginalnego kodu asemblerowego.