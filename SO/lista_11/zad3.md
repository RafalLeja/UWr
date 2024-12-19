## Podstawowymi operacjami na systemie plików są: wyzeruj lub zapal bit w bitmapie i-węzłów albo bloków, wczytaj / zapisz i-węzeł albo blok pośredni (ang. indirect block) albo blok danych. Podaj listę kroków niezbędnych do realizacji funkcji dopisującej n bloków na koniec pliku. Zakładamy, że poszczególne kroki funkcji są zawsze wdrażane synchronicznie. Zadbaj o to by funkcje nie naruszyły spójności systemu plików w przypadku awarii zasilania. Dopuszczamy powstawanie wycieków pamięci.

1. Wczytaj i-węzeł pliku.
2. Oblicz liczbę bloków, które trzeba zaalokować. ( n + bloki pośrednie )
3. Zapal odpowiednie bity w bitmapie bloków.
4. Zapisz bloki danych oraz bloki pośrednie.
4. Zapisz numery bloków w i-węźle pliku. 
5. Zapisz zmodyfikowany i-węzeł pliku.
