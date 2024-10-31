# Zarządzanie Pamięcią C++

Zestaw zadań do samodzielnego wykonania.

Rozwiązania oraz pytania i uwagi należy kierować na skrzynki pocztowe prowadzących:
* bogumil.chojnowski@nokia.com
* pawel.krysiak@nokia.com

Istnieje możliwość drastycznego zwiększenia szansy na odczytanie e-maila przez któregoś z prowadzących poprzez
* umieszczenie obu prowadzących jako adresatów
* umieszczenie w tytule następującego napisu: [PARO2023] Memory Management C++

## Przygotowanie projektu

Utwórz katalog budowania (`mkdir build`), wejdź do niego i wykonaj polecenie

    cmake ..

To wygeneruje drzewo budowania.

**Porada:** możesz podać dodatkowe opcje, takie jak `CMAKE_BUILD_TYPE` i określić generator inny niż domyślny `GNU Makefiles`

    cmake .. -DCMAKE_BUILD_TYPE=Debug -G Ninja

## Alokacja dynamiczna: operatory `new` i `delete`

### Zadanie 1 (0.5 pkt)
Zbuduj program `example_leak` i uruchom test automatycznie sprawdzający wycieki pamięci

    cmake --build . --target example_leak
    ctest -R task1 --output-on-failure

Napraw błędy w pliku `example_leak.cpp` i uruchom test jeszcze raz.

### Zadanie 2 (0.5 pkt)
Zbuduj program `example_leak_array` i uruchom test automatycznie sprawdzający wycieki pamięci

    cmake --build . --target example_leak_array
    ctest -R task2 --output-on-failure

Napraw błędy w pliku `example_leak_array.cpp` i uruchom test jeszcze raz.

**Porada:** Zadeklarowana jest funkcja `destroy_numbers` - spróbuj ją zaimplementować i prawidłowo wywołać.

## Wyjątki - blok `try-catch`

### Zadanie 3 (1 pkt)

Zbuduj program `example_leak_exception` i uruchom test automatycznie sprawdzający wycieki pamięci

    cmake --build . --target example_leak_exception
    ctest -R task3 --output-on-failure

Użyj bloku `try-catch` do obsłużenia sytuacji niepożądanych, takich jak:
1. Niepowodzenie alokacji zasobu, funkcja `allocate_resource`
   - zwraca `NULL` (często)
   - rzuca wyjątkiem typu `std::runtime_error` (bardzo rzadko)
2. Niepowodzenie operacji na zasobie, funkcja `use_resource`
   - rzuca wyjątkami typu `std::runtime_error`
   - nie dopuść do próby **użycia** niezaalokowanego (`NULL`) lub już zwolnionego zasobu
     - `std::terminate` nie da się obsłużyć
3. Niepowodzenie zwolnienia zasobu podczas wywoływania funkcji `free_resource`
   - nie dopuść do próby **zwolnienia** niezaalokowanego (`NULL`) lub już zwolnionego zasobu
     - `std::terminate` nie da się obsłużyć
4. Pozostawienie otwartych zasobów przy opuszczaniu programu
   - **destruktor** podsystemu zasobów sprawdza, czy wszystkie zaalokowane zasoby zostały zwolnione
     - `std::terminate` nie da się obsłużyć

## RAII

### Zadanie 4 (2 pkt)

Zbuduj program `example_leak_raii` i uruchom test automatycznie sprawdzający wycieki pamięci

    cmake --build . --target example_leak_exception
    ctest -R task4 --output-on-failure

Użyj `std::unique_ptr` do zarządzania zasobami:
1. Zmień typ zwracany funkcji `create_event` oraz pierwszego parametru funkcji `process_event` na `std::unique_ptr<Event>`
2. Zastosuj technikę RAII do automatycznego zarządzania czasem życia obiektów
   * **Opcja 1:** Użyj funkcji `free_resource` jako `deleter` w obiektach RAII typu `std::unique_ptr<RESOURCE, deleter>`
      - `std::unique_ptr` utworzony z wartości `NULL` będzie uważał się za niezainicjalizowany i nie wykona deletera
      - tak się szczęśliwie składa, że `allocate_resource` czasem zwraca `NULL`.
   * **Opcja 2:** Jeśli nie czujesz się jeszcze pewnie z biblioteką standardową, napisz własny `ResourceHandler`
      - przejmij zasób w konstruktorze
      - zwolnij zasób w destruktorze
      - nie pozwól się skopiować
3. Zadbaj o czas życia zasobów, niech nie będzie dłuższy niż absolutnie wymagane
   - podczas zwalniania zasobów wypisywane jest podsumowanie czasu życia zasobu.
4. Funkcja `process_event` pobiera tymczasowy zasób i usuwa go wewnątrz.

### Zadanie 5 (1 pkt)

Zbuduj program `example_leak_fds` i uruchom test automatycznie sprawdzający wyciek deskryptora pliku

    cmake --build . --target example_leak_fds
    ctest -R task5 --output-on-failure

Wyjście zawiera informację o niezamkniętym pliku `log.txt`. Skutkuje to uciętymi logami z przebiegu programu, utrudnia to analizę systemu.

Napraw błąd w pliku `example_leak_fds.cpp` (rozszerz implementację klasy `Logger`) i uruchom test ponownie.
