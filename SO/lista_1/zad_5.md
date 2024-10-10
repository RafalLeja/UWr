### Używając programu «lsof» wyświetl zasoby plikopodobne podpięte do procesu przeglądarki «firefox». Wyjaśnij znaczenie poszczególnych kolumn wykazu, po czym zidentyfikuj pliki zwykłe, katalogi, urządzenia, gniazda (sieciowe lub domeny uniksowej) i potoki.

- zasoby plikopodobne: zasoby mające deskryptor pliku, które nie są plikami, np. STDIN, STDOUT, STDERR (0,1,2)
- pliki zwykłe:
- katalogi: aka folder, specjalny plik który zawiera referencje do innych plików i katalogów
- plik urządzenia: plik służący do komunikacji ze sterownikami urządzenia (przez co z samym urządzeniem) za pomocą instrukcji systemowych wej/wyj
- gniazda: sposób dwustronnej komunikacji między procesowej.
- potok: sposób komunikacji między procesami, połączony kanał stdout z stdin dwóch różnch procesów

```
pgrep firefox
lsof -p .

COMMAND   PID  USER   FD      TYPE             DEVICE  SIZE/OFF    NODE NAME
firefox 11500 rafal  cwd       DIR              259,5      4096  131074 /home/rafal
firefox 11500 rafal  rtd       DIR               0,52       540       1 /
firefox 11500 rafal  txt       REG               7,12   1178408     265 /snap/firefox/5014/usr/lib/firefox/firefox
firefox 11500 rafal  DEL       REG                0,1              4138 /memfd:mozilla-ipc
```

- Command: polecenie które uruchomiło proces
- PID: id procesu
- User: właściciel
- FD: numer deskruptora plików, lub:
  - cwd: bieżący katalog
  - err: informacja błędu w NAME
  - pd: katalog rodzica
  - rtd: katalog root
  - mem: plik zmapowany
- TYPE: typ węzła powiązanego z plikiem np.:
  - DIR: katalog
  - REG: plik zwykły
  - SOCK: gniazdo
  - IPv4: gniazdo IPv4
  - FIFO: plik potoku
  - CHR: specjalny plik znakowy
- DEVICE: numer użądzenia
- SIZE/OFF: rozmiar/offset pliku
- NODE: numer węzłą
- NAME: punkt montowania, nazwa systemu plików w którym znajduje się dany plik

```
| grep REG
| grep DIR
| grep -e CHR -e BLK
| grep IPv4
| grep FIFO
```

### Przekieruj wyjście z programu «lsof», przed i po otwarciu wybranej strony, odpowiednio do plików «before» i «after». Czy poleceniem «diff -u before after» jesteś w stanie zidentyfikować nowo utworzone połączenia sieciowe?

```
lsof -p .
> before.txt
> after.txt
colordiff -u before.txt after.txt
```
