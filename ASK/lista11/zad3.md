- **Blok zastąpiony-** w przypadku chybienia w cache, procesor musi odczytać zawartość potrzebnej komórki z pamięci głównej. Może się jednak zdarzyć, że wszystkie linijki z sekcji pamięci cache, do której blok powinien być skopiowany są już w tym momencie zapełnione ważnymi danymi. Trzeba wtedy określić, zawartość której linijki jest najmniej potrzebna i można zastąpić ją nowym blokiem danych z pamięci głównej.
- **Trafienie-** Jeżeli w systemie komputerowym występuje pamięć podręczna, to przy każdym dostępie do adresu w pamięci operacyjnej w celu pobrania rozkazu lub danej, sprzęt procesora przesyła adres najpierw do pamięci podręcznej. W tej pamięci następuje sprawdzenie czy potrzebna informacja jest zapisana w pamięci podręcznej. Jeśli - tak, to mamy do czynienia z tzw. "trafieniem" i potrzebna informacja jest pobierana z pamięci podręcznej.


- **Chybienie** Jeśli żądanej informacji nie ma w pamięci podręcznej, to mamy do czynienia z tzw. "chybieniem" i potrzebna informacja jest pobierana z pamięci operacyjnej z jednoczesnym wprowadzenie jej kopii do pamięci podręcznej. Informacja do pamięci podręcznej nie jest kopiowana w postaci pojedyńczych słów a w postaci bloków słów o ustalonej wielkości. Razem z blokiem informacji, do pamięci podręcznej jest zawsze wpisywana pewna część adresu, która dotyczy początku bloku. Ta część adresu jest później wykorzystywana przy identyfikacji właściwego bloku przy odczycie informacji.

- **Compulosory miss-** następuje, gdy blok jest wprowadzany po raz pierwszy do pamięci podręcznej.

- **Conflict miss-** następuje, gdy kilka bloków mapowanych jest na ten sam zestaw.


| Tag | Index | Offset |
| --- | ------ | ------ |
| 8 | 2 | 2 |

| Address | Tag | Index | Result     | Notes                            |
| ------- | --- | ----- | ---------- | -------------------------------- |
| 0       | 0   |  0    | compulsory | pusta pamięć
| 4       | 0   |  1    | compulsory | pusta pamięć   
| 10      | 1   |  0    | compulsory | pusta pamięć    
| 84      | 8   |  1    | compulsory | pusta pamięć
| 3c      | 3   |  3    | compulsory | pusta pamięć 
| e8      | 0   |  2    | compulsory | pusta pamięć
| c8c     | c8  |  3    | compulsory | pusta pamięć
| a0      | a   |  0    | conflict   | tag 0 zastąpiony
| 4       | 0   |  1    | hit        | pamięć odczytana
| 400     | 40  |  0    | conflict   | tag 1 zastąpiony
| 84      | 8   |  1    | hit        | pamięć odczytana               
| 10      | 1   |  0    | conflict   | tag a zastąpiony
| e8      | e   |  2    | hit        | pamięć odczytana 
| 884     | 88  |  1    | conflict   | tag 0 zastąpiony    
| c8c     | c8  |  3    | hit        | pamięć odczytana
| 0       | 0   |  0    | conflict   | tag 40 zastąpiony


Efektywność: 4/16

Zawartość pamięci:
| Index | Tag |
| ----- | --- |
| 0     | 0   |
|       | 1 |
| 1     | 8 |
|       | 88 |
| 2     | e8 |
| 3     | 3 |
|       | c8 |