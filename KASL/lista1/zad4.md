# Find
szukanie plików

### find /katalog "kwerenda" -akcja

## Składnia

- -name - szukaj plików po nazwie
- -regex - szukaj plików po wyrażeniu regularnym
- -type - szukaj po typie
- -size - szukaj po rozmiarze
- -mtime - szukaj po czasie modyfikacji

## akcje
- -print - (domyślne) wypisz nazwe
- -delete - usuń
- -exec <komenda> {} \; uruchom program na pliku

## przykłady

```bash
# znajdź pliki z zakończeniem .txt
find ~/ -name "*.txt"

# znajdź pliki większe niż 100M
find / -size +100M

# usuń pliki zakończone .log modyfikowane dawniej niż 30 dni
find /var/log -name "*.log" -mtime +30 -delete

# daj uprawnienia plikom zakończonym .sh
find . -name "*.sh" -exec chmod +x {} \;

find ~/Desktop/UWr/ -name "*.md"
```
