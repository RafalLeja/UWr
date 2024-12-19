## Przy pomocy wywołania systemowego unlink(2) można usunąć plik niebędący katalogiem. Powtórz polecenia z zadania 3 dla funkcji usuwającej plik zwykły z katalogu.

1. Wczytaj i-węzeł pliku.
2. Zmniejsz liczbę linków do i-węzła pliku.
3. Usuń wpis z katalogu.
4. Zapisz zmodyfikowany i-węzeł pliku i katalogu.

## Kiedy możliwe jest odwrócenie operacji usunięcia pliku tj. odkasowania (ang. undelete)?
Jeśli żaden blok ani i-węzeł pliku nie został nadpisany, to możliwe jest odzyskanie pliku. W przeciwnym wypadku, plik zostaje utracony.

## Zauważ, że usunięcie pliku nie odbiera procesom możliwości czytania jego zawartości, o ile go otworzyły przed wywołaniem unlink(2). Kiedy w takim razie plik zostanie faktycznie usunięty z dysku?
Gdy wszystkie procesy zakończą pracę z plikiem, to zostanie on oznaczowy jako wolne miejsce ale jego dane nadal istnieją. Dopiero po nadpisaniu danych, plik zostanie usunięty z dysku.