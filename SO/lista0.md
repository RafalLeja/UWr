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
    Słowo kluczowe `volatile` informuje kompilator, że zmienna może być zmieniana przez coś innego niż kod.

   ### Wymień co najmniej dwa scenariusze, w których użycie wskaźników do ulotnej zawartości pamięci jest niezbędne dla poprawności działania programu.
      - Obsługiwanie MMIO
      - Obsługa pamięci współdzielonej