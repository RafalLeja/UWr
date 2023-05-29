Rozważmy pamięć podręczną z **mapowaniem bezpośrednim adresowaną bajtowo**. Używamy adresów 32-bitowych o następującym formacie: (tag, index, offset) = (addr31...10, addr9...5, addr4...0).

- Jaki jest rozmiar bloku w 32-bitowych słowach?
- Ile wierszy ma nasza pamięć podręczna?
- Jaki jest stosunek liczby bitów składujących dane do liczby bitów składujących metadane?

**Mapowanie bezpośrednie** (direct mapping) - każdy blok w pamięci głównej jest odwzorowywany na tylko jeden możliwy wiersz pamięci (tj. jeśli blok jest w cache'u to jest tylko w ściśle określonym miejscu)

- Rozmiar bloku: (addr4...0), czyli min=0, max=11111, więc 32 bajty (czyli 8 4-bajtowych słów)
- Ile wierszy: (addr9...5), czyli min=0, max=11111, czyli 32 wiersze
- dane: 32 bajty
  metadane: tag + valid_bit = 22 + 1 = 23 bity
  stosunek = 23 / (32 \* 8) = 23 / 256