# ls
- wypisz zawartość katalogu

# stat
- wypisz informacje systemowe o pliku
- dowolne formatowanie

# realpath
- wypisz pełną ścieżkę do pliku

# readlink
- odczytaj ścieżkę symbolicznego linku

# dirname
- wypisz katalog zawierający plik

# basename
- wypisz nazwę pliku bez zakończenia

basename $(realpath out.txt) .txt