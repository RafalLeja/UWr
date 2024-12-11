## Implementacja wątków POSIX skomplikowała semantykę niektórych zachowań procesów, które omawialiśmy do tej pory. Co nieoczekiwanego może się wydarzyć w wielowątkowym procesie uniksowym gdy:
## • jeden z wątków zawoła funkcję fork(2) lub execve(2) lub exit_group(2)?
- Fork:
    Tylko jeden wątek zostanie skopiowany, dziecko będzie miało skopiowane mutexy, oraz inne obiekty pthread. W zwiąsku z tym została dodana funkcja pthread_atfork(3). 
- Execve:
    Wszystkie wątki zostaną zakończone, a nowy proces zostanie utworzony.
- Exit_group:
    Wszystkie wątki zostaną zakończone

## • proces zadeklarował procedurę obsługi sygnału «SIGINT», sterownik terminala wysyła do procesu «SIGINT» – w kontekście którego wątek zostanie obsłużony sygnał?
dodolny wątek który nie blokuje sygnału

## • określono domyślną dyspozycję sygnału «SIGPIPE», a jeden z wątków spróbuje zapisać do rury pipe(2), której drugi koniec został zamknięty?
rura jest współdzielona między wątkami, więc sygnał zostanie wysłany do każdego wątku

## • czytamy w wielu wątkach ze pliku zwykłego korzystając z tego samego deskryptora pliku?
kursor jest współdzielony między wątkami, więc każdy wątek będzie czytał z tego samego miejsca