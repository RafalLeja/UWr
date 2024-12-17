## Wyjaśnij czym są punkty montażowe, a następnie wyświetl listę zamontowanych systemów plików i wyjaśnij co znajduje się w poszczególnych kolumnach wydruku.

- punkty montażowe to katalogi lub pliki, które są korzeniem systemu plików, jednocześnie łączącym go z innym systemem plików.

```bash
findmnt
```

## Które z punktów montażowych dają dostęp do instancji pseudo systemów plików?
- /dev, /proc, /sys, /run

```bash
findmnt --pseudo
```

## Na podstawie mount(8) wyjaśnij znaczenie następujących atrybutów punktów montażowych: «relatime», «noexec» i «nodev», a następnie podaj scenariusz, w którym ich zastosowanie jest pożądane.

- relatime:
  -  aktualizuje czas dostępu do pliku tylko wtedy, gdy poprzedni czas dostępu jest wczesniejszy niż czas modyfikacji.
  -  
-  noexec:
  -  zabrania wykonywania plików z danego systemu plików.
  -  podejrzany pendrive, który może zawierać złośliwe oprogramowanie.
- nodev:
  -  zabrania dostępu do urządzeń blokowych i znakowych.
  -  