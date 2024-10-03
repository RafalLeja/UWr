# Słownik

1. - przerwanie sprzętowe: występuje asynchronicznie, jest generowane przez urządzenia zewnętrzne, np. klawiatura, myszka, dysk twardy, itp. Zawsze wraca do następnej instrukcji po przerwaniu.
   - wyjątek procesora: występuje synchronicznie, jest generowane przez procesor, np. dzielenie przez zero, overflow, page fault itp. Wracamy do obsługi wyjątku, a następnie do następnej instrukcji.
   - pułapka: występuje synchronicznie, jest generowane przez wykonywanie instrukcji. Najczęściej występuje przy syscallach, takich jak `read`, `fork`, `exec`, itp. Wracamy do następnej instrukcji po obsłużeniu pułapki.
2. - obsługa przerwań: obv.
   - wektor przerwań: wektor przechowujący adresy procedur obsługi przerwań dla poszczególnych numerów przerwań.
   - procedura obsługi przerwań: funkcja, która jest wywoływana w momencie wystąpienia przerwania.
   - tryb jądra: tryb, w którym system operacyjny ma dostęp do wszystkich zasobów sprzętowych.
3. - sekcja: potrzebne podczas linkowania, opisuje fragment ELF-a, np. `code`, `data`, `bss`, itp.
   - segment: potrzebne na runtime, część ELF-a składająca się z sekcji, która będzie wczytana do pamięci, np. `.text`, `.data`, `.bss`, itp.
   - nagłówek: opisuje strukturę pliku ELF, np. ilość sekcji, ilość segmentów, adresy początkowe, itp.
4. - przestrzeń adresowa: zakres adresów, które proces może używać.
   - auxilary vector: wektor, który zawiera informacje o środowisku np. flagi, entry point, itp.

# Zadanie 1
 ### W jakim scenariuszu wyjątek procesora nie oznacza błędu czasu wykonania programu?
    W przypadku gdy wyjątek jest obsługiwany przez program, a nie przez system operacyjny.
 ### Kiedy pułapka jest generowana w wyniku prawidłowej pracy programu?
    Przy wykonywaniu syscalla, np. `read`, `fork`, `exec`, itp.

# Zadanie 2
 ### Co robi procesor przed pobraniem pierwszej instrukcji procedury obsługi przerwania i po natrafieniu na instrukcję powrotu z przerwania?
    Zapisuje i wczytuje stan procesora na stosie.
 ### Czemu procedura obsługi przerwania powinna być wykonywana w trybie jądra i używać stosu odrębnego od stosu użytkownika?
    Aby zapobiec błędom w trakcie obsługi przerwania, np. nadpisaniu ważnych danych na stosie użytkownika.

# Zadanie 3
 ### Co opisują nagłówki programy?
 | Sekcja      | Przeznaczenie |
| ----------- | ------------- |
| `.text`     | Kod maszynowy skompilowanego programu. |
| `.rodata`   | Dane tylko do odczytu, np. sekwencje znaków niezmienialnych `string` używanych w funkcji `printf` oraz tabele skoków dla instrukcji `switch`.              |
| `.data`     | Zainicjalizowane zmienne globalne oraz `static`. Lokalne zmienne są trzymane na stosie w trakcie uruchomienia programu (run time) i nie pojawiają się ani w sekcji `.data`, ani w `.bss`.              |
| `.bss`      | Niezainicjalizowane zmienne globalne oraz `static`, włącznie ze zmiennymi zainicjalizowanymi na 0, ta sekcja nie zajmuje miejsca w pliku relokowalnym, jest jedynie placeholderem.              |
| `.symtab`   | Tabela symboli z informacją o funkcjach i zmiennych globalnych, które są zdefiniowane i do których odwołuje się w programie.              |
| `.rel.text` | Lista lokalizacji z sekcji `.text`, która zostanie zmodyfikowana w trakcie linkowania tego pliku relokowalnego z innymi. W ogólności instrukcje, które wywołują &#34;zewnętrzne &#34;*(ang. external)* funkcje lub odwołują się do zmiennych globalnych, będą musiały być zmodyfikowane, jednak funkcje wywoływane lokalnie nie muszą być modyfikowane.            |
| `.rel.data` | Informacje o relokacji dla zmiennych globalnych, do których występują odwołania lub są zdefiniowane w tym module. W ogólności są to zainicjalizowane zmienne globalne, których wartością początkową jest adres oraz funkcje zdefiniowane &#34;zewnętrznie &#34;.              |
| `.debug`    | Lista symboli do debugowania, zawiera lokalne zmienne i definicje typów (`typedef`), zmienne globalne zdefiniowane przez program i te, do których się odwołuje, jak i oryginalny kod źródłowy w języku C. Aby sekcja ta powstała, należy skompilować program z flagą `-g`.              |
| `.line`     | Mapowanie pomiędzy liniami z pliku źródłowego a instrukcjami kodu maszynowego z sekcji `.text`, podobnie pojawia się po użyciu flagi `-g`.              |
| `.strtab`   | Tablica `string`ów dla sekcji tabeli symboli `.symtab` oraz `.debug`, jak i nazw sekcji w nagłówkach.

 ### Skąd system operacyjny wie, pod jakim adresem ma umieścić segmenty programu i gdzie położona jest pierwsza instrukcja programu?
System operacyjny wie pod jakim adresem ma umieścić segmenty programu dzięki segment header table. Adres pierwszej instrukcji znajduje się w headerze ELF.

# Zadanie 4
   ### W jaki i sposób jądro musi przygotować przestrzeń adresową procesu?
     - Czyszczenie flag
     - przygotowanie auxv i stosu
   ### Co musi znajdować się na stosie w momencie wywołania procedury «_start»?
    - Argumenty dla `main`
    - `argc`
    - `argv`
    - `envp` - stringi w środowisku
    - auxilary vector

  ### W jaki sposób wywołać funkcję jądra?
    instrukcją `syscall`
  ### W których rejestrach należy umieścić argumenty?
    numer syscalla w `rax`, argumenty w `rdi`, `rsi`, `rdx`, `r10`, `r8`, `r9`
  ### Gdzie można spodziewać się wyników i jak jądro sygnalizuje niepowodzenie wywołania systemowego?
    Wyniki zwracane są w `rax`, a błąd to wartość od -4095 do -1 zapisywana w `rax`.

# Zadanie 5
   ### Opisz znaczenie słowa kluczowego «volatile» w języku C.
    Słowo kluczowe `volatile` informuje kompilator, że zmienna może być zmieniana asynchronicznie przez coś innego niż kod.

   ### Wymień co najmniej dwa scenariusze, w których użycie wskaźników do ulotnej zawartości pamięci jest niezbędne dla poprawności działania programu.
      - Obsługiwanie MMIO
      - Obsługa pamięci współdzielonej
      - Obsługa przerwań

# Zadanie 6

**Tłumaczenie adresów** to proces znajdowania adresu fizycznego z adresu wirtualnego. Architektura x86-64 używa czteropoziomowej tablicy stron:

| `63-48` | `47-39` | `38-29` | `29-21` | `20-12` | `11-0` |
| ------- | ------- | ------- | ------- | ------- | ------ |
|         | level 4 | level 3 | level 2 | level 1 | offset |

16 najbardziej znaczących bitów adresu jest nieużywane.

Algorytm translacji dla pojedynczej tabeli stron wygląda następująco:
![](https://i.imgur.com/hmJlvbK.png)

A dla stron procesów z rodziny x86-64: używamy rejestru `%cr3` przechowującego adres fizyczny czwartego poziomu tabeli stron (aby ostatecznie dostać się do adresu, który chcemy). Algorytm ten przebiega w następujący sposób:
1. Używamy `%cr3` i indeksu z L4 z wirtualnego adresu aby dotrzeć do poziomu L3 tabeli stron.
2. Używamy adresu tabeli stron L3 i indeksu L3 aby dotrzeć do poziomu L2 tabeli stron.
3. Używamy adresu tabeli stron L2 i indeksu L2 aby dotrzeć do poziomu L1 tabeli stron.
4. Używamy adresu tabeli stron L1 i indeksu L1 aby dotrzeć do żądanego adresu fizycznego.
5. Używamy żądanego adresu fizycznego i przesunięcia (offset) do uzyskania rzeczywistego adresu fizycznego.

**Bufor TLB** *(ang. translation lookaside buffer)* (czasami **pamięć asocjacyjna**) to urządzenie sprzętowe służące do odwzorowywania adresów wirtualnych na fizyczne bez konieczności sięgania do tabeli stron. Zwykle jest ono zlokalizowane wewnątrz jednostki MMU i składa się z niewielkiej liczby pozycji - każda pozycja zawiera informacje dotyczące jednej strony.

# Zadanie 7

### Na podstawie śladu wykonania programu zidentyfikuj, które z wywołań systemowych są używane przez procedury: «opendir», «readdir», «printf» i «closedir». 
   ```
opendir("libapue/" <unfinished ...>
SYS_openat(0xffffff9c, 0x7ffd5fa26c41, 0x90800, 0)                        = 3
SYS_newfstatat(3, 0x7f9fd49c844f, 0x7ffd5fa24ec0, 4096)                   = 0
SYS_318(0x7f9fd4a114d8, 8, 1, 4096)                                       = 8
SYS_brk(0)                                                                = 0x55d300309000
SYS_brk(0x55d30032a000)                                                   = 0x55d30032a000
<... opendir resumed> )                                                   = 0x55d3003092a0
readdir(0x55d3003092a0 <unfinished ...>
SYS_getdents64(3, 0x55d3003092d0, 0x8000, 120)                            = 144
<... readdir resumed> )                                                   = 0x55d3003092d0
puts(".." <unfinished ...>
SYS_newfstatat(1, 0x7f9fd49c844f, 0x7ffd5fa24df0, 4096)                   = 0
SYS_write(1, "..\n", 3..
)                                                   = 3
<... puts resumed> )                                                      = 3
readdir(0x55d3003092a0)                                                   = 0x55d3003092e8
puts("error.c" <unfinished ...>
SYS_write(1, "error.c\n", 8error.c
)                                              = 8
<... puts resumed> )                                                      = 8
readdir(0x55d3003092a0)                                                   = 0x55d300309308
puts("libapue.a" <unfinished ...>
SYS_write(1, "libapue.a\n", 10libapue.a
)                                           = 10
<... puts resumed> )                                                      = 10
readdir(0x55d3003092a0)                                                   = 0x55d300309328
puts("error.o" <unfinished ...>
SYS_write(1, "error.o\n", 8error.o
)                                              = 8
<... puts resumed> )                                                      = 8
readdir(0x55d3003092a0)                                                   = 0x55d300309348
puts("." <unfinished ...>
SYS_write(1, ".\n", 2.
)                                                    = 2
<... puts resumed> )                                                      = 2
readdir(0x55d3003092a0 <unfinished ...>
SYS_getdents64(3, 0x55d3003092d0, 0x8000, 119)                            = 0
<... readdir resumed> )                                                   = 0
closedir(0x55d3003092a0 <unfinished ...>
SYS_close(3)                                                              = 0
```
   
   - `opendir` - `SYS_openat(0xffffff9c, 0x7efe951e121b, 0x80000, 0)`
   - `readdir` - `SYS_getdents64(3, 0x55d3003092d0, 0x8000, 120) `
   - `printf` - `SYS_write(1, "..\n", 3..`
   - `closedir` - `SYS_close(3)`

### Do czego służy wywołanie systemowe «brk»?
Wywołanie systemowe `brk` służy do zmiany rozmiaru segmentu danych procesu. W przypadku, gdy argument `addr` jest równy 0, `brk` zwraca aktualny adres końca sterty. W przeciwnym przypadku, `brk` zmienia rozmiar sterty na taki, aby kończyła się na adresie `addr`. Używane przez funkcje `malloc` i `free`.

###  Używając debuggera «gdb» i polecenia «catch syscall brk» zidentyfikuj, która funkcja używa «brk»
```
Catchpoint 1 (call to syscall brk), __brk (addr=addr@entry=0x0) at ../sysdeps/unix/sysv/linux/brk.c:36
36      ../sysdeps/unix/sysv/linux/brk.c: No such file or directory.
(gdb) backtrace
#0  __brk (addr=addr@entry=0x0) at ../sysdeps/unix/sysv/linux/brk.c:36
#1  0x00007ffff7fe27ee in frob_brk () at ../sysdeps/unix/sysv/linux/dl-sysdep.c:36
#2  _dl_sysdep_start (start_argptr=start_argptr@entry=0x7fffffffd970, dl_main=dl_main@entry=0x7ffff7fe48e0 <dl_main>)
    at ../elf/dl-sysdep.c:230
#3  0x00007ffff7fe4598 in _dl_start_final (arg=0x7fffffffd970) at ./elf/rtld.c:507
#4  _dl_start (arg=0x7fffffffd970) at ./elf/rtld.c:596
#5  0x00007ffff7fe3298 in _start () from /lib64/ld-linux-x86-64.so.2
#6  0x0000000000000001 in ?? ()
#7  0x00007fffffffdbff in ?? ()
#8  0x0000000000000000 in ?? ()
```

# Zadanie 8

### Pod kontrolą narzędzia «strace» uruchom program «2_cat» korzystający bezpośrednio z wywołań systemowych do interakcji ze standardowym wejściem i wyjściem. Pokaż, że program oczekuje na odczyt na deskryptorze pliku 0 i pisze do pliku o deskryptorze 1. 

```
read(0, halohalo
"halohalo\n", 4096)             = 9
write(1, "halohalo\n", 9halohalo)               = 9
read(0, "", 4096)                       = 0
exit_group(0)                           = ?
```

### Zmodyfikuj program tak, by czytał z pliku podanego w linii poleceń. Co się stanie, jeśli przekażesz ścieżkę do katalogu zamiast do pliku zwykłego?
```
openat(AT_FDCWD, "libapue/", O_RDWR|O_CREAT, 0644) = -1 EISDIR (Is a directory)
read(-1, 0x7ffc42c0f0d0, 4096)          = -1 EBADF (Bad file descriptor)
write(2, "read error: Bad file descriptor\n", 32read error: Bad file descriptor
) = 32
exit_group(1)
```