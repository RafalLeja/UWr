Mamy system z pamięcią operacyjną adresowaną bajtowo. Szerokość szyny adresowej wynosi 12. Pamięć podręczna ma organizację sekcyjno-skojarzeniową o dwuelementowych zbiorach, a blok ma 4 bajty. Dla podanego niżej stanu pamięci podręcznej wyznacz, które bity adresu wyznaczają: offset, indeks, znacznik (ang.tag). Wszystkie wartości numeryczne podano w systemie szesnastkowym.
| Indeks | Znacznik | Valid | B0 | B1 | B2 | B3 |
| ------ | -------- | ----- | --- | --- | --- | --- |
| 0 | 00 | 1 | 40 | 41 | 42 | 43 |
| | 83 | 1 | FE | 97 | CC | D0 |
| 1 | 00 | 1 | 44 | 45 | 46 | 47 |
| | 83 | 0 | - | - | - | - |
| 2 | 00 | 1 | 48 | 49 | 4A | 4B |
| | 40 | 0 | - | - | - | - |
| 3 | FF | 1 | 9A | C0 | 03 | FF |
| | 00 | 0 | - | - | - | - |

Określ, które z poniższych operacji odczytu wygenerują trafienie i ew. jakie wartości wczytają:

| Adres | Trafienie? | Wartość |
| ----- | ---------- | ------- |
| 832   | ?          | ?       |
| 835   | ?          | ?       |
| FFD   | ?          | ?       |

Szyna wygląda następująco:
| Tag | Index | Offset |
| --- | ------ | ------ |
| 8 | 2 | 2 |

Zatem:
| Adres | Tag | Index | Offset | Trafienie? | Wartość |
| ----- | --- | ----- | ------ | ---------- | ------- |
| 832 | 83 | 0 | 2 | tak | CC |
| 835 | 83 | 1 | 1 | nie | - |
| FFD | FF | 3 | 1 | tak | C0 |

0x4A??