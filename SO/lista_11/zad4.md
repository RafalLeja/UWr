## Przy pomocy wywołania systemowego rename(2) można przenieść atomowo plik do katalogu znajdującego się w obrębie tego samego systemu plików. Czemu «rename» zakończy się błędem «EXDEV» kiedy próbujemy przenieść plik do innego systemu plików?

- rename opiera się na hardlinkach, które nie mogą przechodzić między systemami plików

## Powtórz polecenia z zadania 3 dla funkcji przenoszącej plik między dwoma różnymi katalogami w obrębie tego samego systemu plików. Zakładamy, że w katalogu docelowym jest wystarczająco dużo miejsca na dodanie wpisu. Pamiętaj, że wpis katalogu nie może przecinać granicy między blokami!

1. Wczytaj i-węzeł pliku.
2. Zwiększ liczbę linków do i-węzła pliku.
6. Zapisz zmodyfikowany i-węzeł katalogu docelowego.
3. Zapisz katolog docelowy.
4. Zapisz zmodyfikowany i-węzeł pliku.
5. Usuń wpis z katalogu źródłowego.
7. Zmniejsz liczbę linków do i-węzła pliku.
6. Zapisz zmodyfikowany i-węzeł katalogu źródłowego.
8. Zapisz zmodyfikowany i-węzeł pliku.