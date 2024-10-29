### Uruchom potok (ang. pipeline) «ps -ef | grep sh | wc -l > cnt» w powłoce utworzonej przy pomocy polecenia «strace -o pipeline.log -f dash». 
```bash
strace -o pipeline.log -f dash
ps -ef | grep sh | wc -l > cnt
cat pipeline.log
```
### Na podstawie zawartości pliku «pipeline.log» opisz jak powłoka realizuje funkcje łączenia procesów rurami (ang. pipe) i wykonuje przekierowanie standardowego wyjścia do pliku. W szczególności wskaż które procesy i w jakiej kolejności będą wołały następujące wywołania systemowe: openat(2) z flagą «O_CREAT» (realizuje creat(2)), dup2(2), pipe(2), close(2), clone(2) (realizuje fork(2)) i execve(2). Zwróć szczególną uwagę na to kiedy powłoka tworzy rury i kiedy są zamykane ich poszczególne końce.
```bash
grep -E 'openat|dup2|pipe|close|clone|execve' pipeline.log
```