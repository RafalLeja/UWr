## Dodaj do pliku ~/.bashrc definicje (w postaci aliasów bądź funkcji) kilku prostych, ale często przydatnych poleceń:

### - ll — wypisuje zawartość (podanego lub bieżącego) katalogu korzystając z polecenia ls z opcjami -lAFbhv oraz --color=always (wyjaśnij, co znaczą te opcje) i w celu stronicowania listingu korzysta z pagera less z opcjami -XFR (wyjaśnij, co one znaczą).

```bash
alias ll='ls -lAFbhv --color=always | less -XFR'
```
Flagi:
- ls:
  - -l - wyświetla listę w formie długiej
  - -A - wyświetla wszystkie pliki oprócz . i ..
  - -F - dodaj znak "*/=>@|" do wpisu
  - -b - wyświetla znaki specjalne w formie znaków ucieczki
  - -h - wyświetla rozmiar w formie czytelnej dla człowieka
  - -v - sortuje po nazwie w sposób "wersji"
  - --color=always - koloruje wynik
- less:
  - -X - niektóre znaki nie są wysyłane do terminala, np żeby terminal nie zrobił clear
  - -F - automatycznie przechodzi do trybu bezczynności, jeśli cały plik mieści się na jednym ekranie
  - -R - pozwala na wyświetlanie kolorów


### - gentmp — wypisuje na standardowe wyjście napis tmp-YYYYMMDDhhmmss zawierający w miejscu odpowiednich liter bieżący czas.

```bash
alias gentmp='echo tmp-$(date +%Y%m%d%H%M%S)'

man date
```

### - genpwd — wypisuje na standardowe wyjście napis złożony z 32 losowo wybranych znaków ze zbioru [3-9A-HJ-NP-Z] (pomijamy znaki, które można pomylić z innymi, np. 0O itp.), zakończony znakiem nowego wiersza. Jako źródła losowości użyj /dev/urandom. Wszystkie ciągi powinny być jednakowo prawdopodobne

```bash
alias genpwd='cat /dev/urandom | tr -dc 3-9A-HJ-NP-Z | head -c 32; echo'
```

Flagi:
- tr:
  - -d - usuwa znaki z podanego zbioru
  - -c - komplement zbioru znaków (odwrotność zbioru)
- head:
  - -c - ogranicza ilość znaków do podanej liczby
- echo - wyświetla znak nowego wiersza
