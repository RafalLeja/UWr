## Na podstawie [2, 14.4] opowiedz jaka motywacja stała za wprowadzeniem wywołania poll(2) [3, 63.2.2] do systemów uniksowych?
Potrzeba informacji który deskryptor jest gotowy do odczytu/zapisu bez blokowania procesu

## Czemu lepiej konstruować oprogramowanie w oparciu o poll, niż o odpytywanie deskryptorów albo powiadamianie o zdarzeniach bazujące na sygnale «SIGIO»?
poll informuje nas który deskryptor jest gotowy do odczytu/zapisu bez blokowania procesu, a pozostałe metody wymagają sprawdzenia wszystkich deskryptorów

## Na jakich plikach można oczekiwać na zdarzenia przy pomocy poll(2) [3, 63.2.3]?
- Zwykłe pliki:
    select/poll zawsze zwróci read/write
- Terminal:
    select/poll zwraca:
        - read: kiedy jest dostępne coś do odczytu
        - write: kiedy można coś zapisać
        - read+write: kiedy terminal został zamknięty
- Rury i Fifo:
    select/poll zwraca:
        - read (POLLHUP): kiedy drugi koniec rury został zamknięty i nie ma danych
        - read (POLLIN): kiedy jest dostępne coś do odczytu
        - read (POLLIN | POLLHUP): kiedy jest dostępne coś do odczytu i drugi koniec rury został zamknięty
        - write (POLLERR): kiedy drugi koniec rury został zamknięty i bufor jest pełny
        - write (POLLOUT): kiedy można coś zapisać
        - write (POLLERR | POLLOUT): kiedy drugi koniec rury został zamknięty i bufor nie jest pełny
- Gniazda sieciowe:
    select/poll zwraca:
        - read (POLLIN): kiedy jest dostępne coś do odczytu
        - write (POLLOUT): kiedy można coś zapisać
        - read (POLLIN): kiedy gniazdo zostało połączone
        - x (POLLPRI): Out-of-band data dostępne
        - read+write (POLLIN | POLLOUT | POLLRDHUP): kiedy drugi koniec gniazda został zamknięty

## Czemu wszystkie deskryptory przekazywane do poll powinno skonfigurować się do pracy w trybie nieblokującym?
Aby poll nie blokował się na deskryptorach

## Jak zapewnić, żeby wywołania connect(2), accept(2), read(2) i write(2) na gnieździe sieciowym zawsze zwróciły «EWOULDBLOCK» zamiast blokować się w jądrze [7, 16]?
Ustawić gniazdo w tryb nieblokujący

## Chcemy by po wywołaniu poll(2) pierwsza instancja wyżej wymienionych wywołań systemowych nie zwróciła «EWOULDBLOCK». Jaka wartość musi być wpisana przez jądro do pola «revents» struktury «pollfd» dla danego deskryptora pliku, żeby mieć tę pewność?
Pole revents musi być ustawione na POLLIN, POLLOUT, POLLERR, POLLHUP, POLLRDHUP, POLLPRI