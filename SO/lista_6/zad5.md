### Jakie zadania pełni procedura exit(3) z biblioteki standardowej?
uruchamia procedurę zarejestrowaną przez atexit(3) i on_exit(3),
opróznia i zamyka strumienie z biblioteki stdio(3),
usuwa pliki tymczasowe utworzone przez tmpfile(3),
zamyka program i zwraca kod wyjścia do systemu operacyjnego.

### Opisz problemy z buforowaniem plików, które mogą wystąpić dla strumieni biblioteki stdio(3) w przypadku użycia wywołań fork(2), execve(2) i _exit(2).
- fork: kopuije bufor rodzica, więc wypiszemy duplikat bufora
- execve: bufor może zostać utracony
- _exit: bufor może zostać utracony

### Jak zapobiec tym problemom?
wywołaj fflush(3) przed fork(2), execve(2) i _exit(2)

### Jaka jest domyślna strategia buforowania strumienia związanego z (a) plikiem terminala (b) plikiem zwykłym (c) standardowym wyjściem błędów «stderr».
- a) buforowany po wierszach
- b) buforowany w pełni
- c) niebuforowany

### Piszesz program który używa biblioteki «stdio». Działanie programu da się przerwać sygnałem «SIGINT». Ma on wtedy opróżnić wszystkie bufory otwartych strumieni i dopiero wtedy wyjść. Zaproponuj rozwiązanie pamiętając, że w procedurach obsługi sygnału nie wolno korzystać z funkcji, które nie są wielobieżne.
jak wiemy, exit(3) opróżnia bufory, więc wystarczy wywołać exit(3) w procedurze obsługi sygnału