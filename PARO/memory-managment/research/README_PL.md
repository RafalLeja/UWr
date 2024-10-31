# Projekt badawczy

## Wymagane biblioteki

W przeciwieństwie do zadań obowiązkowych dodatkowe wymaga większych umiejętności.

Przede wszystkim, do zbudowania projektu wymagane są dodatkowe biblioteki:

- GTest https://github.com/google/googletest.git

Pobranie i skonfigurowanie ich pozostawiono w gestii badacza.

## Algorytm bloków bliźniaczych

Obecnie implementacja trzyma informacje o zajętych blokach w `std::vector` - pod każdym indeksem `i` znajduje się kolejny `std::vector` z informacją o wolnych blokach rozmiaru `2^i`

Implementacja ta jest dość efektywna pamięciowo (zajmuje mało miejsca), ale cierpi na niedostatek wydajności:

- szukanie i składanie wolnych bloków bliźniaczych jest kosztowne
- informacje są rozsiane po RAM - pamięć podręczna procesora nie może zostać wykorzystana do zwiększenia prędkości.

### Zadanie

Należy dostosować implementację algorytmu tak, aby pole `Heap::heap` stało się tablicą o ustalonym rozmiarze, oraz nadać jej właściwości struktury danych: kopca.

Pod indeksem `i` powinna znaleźć się informacja o zajętości bloku: 0 oznacza, że blok oraz wszystkie bloki mniejsze są wolne — blok może zostać zaalokowany lub podzielony na mniejsze.

Podbloki indeksu `i` znajdują się pod indeksami `2*i+1` oraz `2*i+2` - jeśli oba są wolne, to wolny jest też blok `i`-ty. Należy przeprowadzić procedurę scalania bloków (czyli `heap[i] = 0`) rekurencyjnie.

Alokowanie bloku rozmiaru dowolnego `N` bajtów: musimy znaleźć najmniejszy wolny blok o rozmiarze co najmniej `N`. W tym celu należy obliczyć zakres indeksów zawierający bloki o odpowiednim rozmiarze `S`:

Dla rozmiaru strony `P = 64`, optymalny index `I` można znaleźć w podanych zakresach:

 N  |  S | I_min     ; I_max
---:|---:|--------------------:
  1 |  1 | 2^5+1 = 33; 2^6 = 64
  2 |  2 | 2^4+1 = 17; 2^5 = 32
  3 |  4 | 2^3+1 =  9; 2^4 = 16
  7 |  8 | 2^2+1 =  5; 2^3 =  8
  9 | 16 | 2^1+1 =  3; 2^2 =  4
 29 | 32 | 2^0+1 =  1; 2^1 =  2
 40 | 64 | 0


Jeśli nie ma wolnych bloków optymalnego rozmiaru, należy podzielić większy blok. Jeśli większych bloków też nie ma, to nie jest dostępny ciągły obszarze pamięci o wymaganym rozmiarze.

### Testy automatyczne

Testy dołączone są do projektu. Do ich skompilowania niezbędna jest biblioteka `GTest`. Powinny wystarczyć do zaimplementowania zadania. 

- `buddy_allocation/tests/tests_allocation.cpp`
- `buddy_allocation/tests/tests_deallocation.cpp`

Można dopisywać też własne testy dla znalezionych przypadków.

### Testy manualne

W pliku `main.cpp` znajduje się kilka funkcji, które pełnią rolę testów manualnych. Uruchamiając program można zweryfikować działanie napisanego kodu na własne oczy.

O ile jest to metoda powolna i kosztowna porównując do testów automatycznych, to można ją stosować bez dostępu do biblioteki GTest
