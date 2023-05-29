- **Blok zastąpiony-** w przypadku chybienia w cache, procesor musi odczytać zawartość potrzebnej komórki z pamięci głównej. Może się jednak zdarzyć, że wszystkie linijki z sekcji pamięci cache, do której blok powinien być skopiowany są już w tym momencie zapełnione ważnymi danymi. Trzeba wtedy określić, zawartość której linijki jest najmniej potrzebna i można zastąpić ją nowym blokiem danych z pamięci głównej.
- **Trafienie-** Jeżeli w systemie komputerowym występuje pamięć podręczna, to przy każdym dostępie do adresu w pamięci operacyjnej w celu pobrania rozkazu lub danej, sprzęt procesora przesyła adres najpierw do pamięci podręcznej. W tej pamięci następuje sprawdzenie czy potrzebna informacja jest zapisana w pamięci podręcznej. Jeśli - tak, to mamy do czynienia z tzw. "trafieniem" i potrzebna informacja jest pobierana z pamięci podręcznej.


- **Chybienie** Jeśli żądanej informacji nie ma w pamięci podręcznej, to mamy do czynienia z tzw. "chybieniem" i potrzebna informacja jest pobierana z pamięci operacyjnej z jednoczesnym wprowadzenie jej kopii do pamięci podręcznej. Informacja do pamięci podręcznej nie jest kopiowana w postaci pojedyńczych słów a w postaci bloków słów o ustalonej wielkości. Razem z blokiem informacji, do pamięci podręcznej jest zawsze wpisywana pewna część adresu, która dotyczy początku bloku. Ta część adresu jest później wykorzystywana przy identyfikacji właściwego bloku przy odczycie informacji.

- **Compulosory miss-** następuje, gdy blok jest wprowadzany po raz pierwszy do pamięci podręcznej.

- **Conflict miss-** następuje, gdy kilka bloków mapowanych jest na ten sam zestaw.


| Tag | Index | Offset |
| --- | ------ | ------ |
| 8 | 2 | 2 |

| Address | Tag | Index | Offset | Result     | Notes                            |
| ------- | --- | ----- | ------ | ---------- | -------------------------------- |
| 0       | 0   | 00000 | 00000  | compulsory | pusta pamięć
| 4       | 0   | 00000 | 00100  | hit        | (z wpisu 0)                      |
| 10/16   | 0   | 00000 | 10000  | hit        | (z wpisu 0)                      |
| 84/132  | 0   | 00100 | 00100  | compulsory | pusta pamięć
| 3c/60   |  
| e8/232  | 0   | 00111 | 01000  | compulsory |
| c8c/3212| s
| a0/160  | 0   | 00101 | 00000  | compulsory |
| 4       |
| 400/1024| 1   | 00000 | 00000  | conflict   | zastąpi poprzedni wpis w i=0     |
| 84/132  | 0   | 00000 | 11100  | conflict   | j/w                              |
| 10/16   | 0   | 00100 | 01100  | hit        | (z wpisu 132)                    |
| e8/232  | 11  | 00000 | 11000  | conflict   | zastąpi wpis o i=0               |
| 884/2180| 0   | 00101 | 10100  | hit        | (z wpisu 160)                    |
| c8c/3212| 10  | 00100 | 00100  | conflict   | zastąpi poprzedni wpis o i=00100 |
|0        |

Efektywność: 4/12

Zawartość pamięci:
| Index | Tag |
| ----- | --- |
| 0 | 11 |
| 100 | 10 |
| 101 | 0 |
| 111 | 0 |