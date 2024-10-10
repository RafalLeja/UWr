### Wbudowanym poleceniem powłoki «time» zmierz czas wykonania długo działającego procesu, np. polecenia «find /usr».
```
time find /usr

real	0m1,551s
user	0m0,306s
sys	    0m0,471s
```

### Czemu suma czasów user i sys (a) nie jest równa real (b) może być większa od real?
- real: realny czas od ENTER do wydrukowania wyniku
- user: czas spędzony w trybie użytkownika
- sys: czas spędzony w trybie jądra

- sys + user < real:
    w czasie wykonywania procesu system wykonał inne procesy
- sys + user > real
    system ma wiele rdzeni i mógł wykonywać prace równolegle na wielu rdzeniach

### Poleceniem «ulimit» nałóż ograniczenie na czas wykonania procesów potomnych powłoki tak, by limit się wyczerpał. Uruchom ponownie wybrany program – który sygnał wysłano do procesu?

```
seq 1000000 | grep 9

Killed

sudo strace -p $(pgrep longFind)
```