### Na podstawie kodu źródłowy sinit.c1 opowiedz jakie zadania pełni minimalny program rozruchowy sinit.

1. Początkowy proces init
2. Uruchamianie rcinit
3. Grzebanie zombii i sierot
4. Pętla słuchania sygnałów
5. Wyłączanie maszyny

### Jakie akcje wykonuje pod wpływem wysyłania do niego sygnałów wymienionych w tablicy «sigmap»?

- SIGUSR1: wyłącz maszyne
- SIGCHLD: pogrzeb dzieci
- SIGALRM: pogrzeb dzieci
- SIGINT: restart maszyny

### Do czego służą procedury sigprocmask(2) i sigwait(3)?

- sigprocmask(2) - zmienia maskę sygnałów blokowanych przez proces
- sigwait(3) - czeka na sygnał z listy sygnałów

### W jaki sposób grzebie swoje dzieci?

```C
sigreap(void)
{
    while (waitpid(-1, NULL, WNOHANG) > 0)
        ;
	alarm(TIMEO);
}
```

waitpid(-1, NULL, WNOHANG) - czeka na zakończenie dowolnego procesu potomnego, wróć natychmiast jeśli żaden proces nie zakończył działania,
alarm(TIMEO) - ustawia alarm na 30 sekund
