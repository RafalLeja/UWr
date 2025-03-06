# GREP (Global Regular Expression Print)
znajdowanie wzorców w plikach

### grep -FLAGI "klucz" plik/katalog

## REGEX - Wyrażenia regularne


- [a-z] - litery od a do z
- [abx] - a, b lub x
- [^abx] - wszystko oprócz a, b i x
- . - dowolny znak
- * - zero lub więcej wystąpień poprzedniego znaku
- + - jedno lub więcej wystąpień poprzedniego znaku
- ? - zero lub jedno wystąpienie poprzedniego znaku

## Flagi
kontrola wyrażeń
- -e - wyrażenie regularne
- -f - plik z wyrażeniami regularnymi
- -i - ignoruj wielkość liter
- -v - wyklucz pasujące linie

wyjście 
- -c - zlicz pasujące linie
- --color=always - koloruj wynik
- -l - lista plików z pasującymi liniami
- -L - lista plików bez pasujących linii
- -o - wyświetl tylko pasujące fragmenty

wejście
- -D - obsługa urządzenia
- -r - rekurencyjnie bez linków
- -R - rekurencyjnie z linkami

## Przykłady

```bash
# znajdź słowo error w pliku log.txt
grep "error" log.txt

# znajdź "error" w katalogu
grep -r "error" /var/log

grep "e[a-z]*r" log.txt 
# pasuje np. do 'error', 'enter', 'eager'

grep -r "Zadanie 2" ~/Desktop/UWr/
```