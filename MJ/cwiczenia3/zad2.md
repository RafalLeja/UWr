## Czym s¡ rzadkie reprezentacje wektorowe sªów (wykorzystuj¡ce TF-IDF i konteksty)?

TFIDF - Term Frequency Inverse Document Frequency - to metoda oceny ważności słowa w kontekście dokumentu. Wartość TF-IDF rośnie wraz z częstością występowania słowa w dokumencie, ale jest kompensowana przez częstość występowania słowa w całym korpusie dokumentów. W ten sposób TF-IDF pozwala na wykrycie słów, które są unikalne dla danego dokumentu i mają znaczenie w jego kontekście.

Reprezentacja słów w przestrzeni n wymiarowej gdzie n to moc zbioru słów w danym korpusie.
Każde słowo jest reprezentowane jako wektor w tej przestrzeni, gdzie każda współrzędna wektora odpowiada jednemu słowu z korpusu.

## Dlaczego nie jest to rozwi¡zanie perfekcyjne (sªaba wskazówka: pi¦kna »aglówka; ±liczny »aglowiec).

- piękna żaglówka i liczny żaglowiec mają podobne znaczenie, ale mogą mieć bardzo różne reprezentacje wektorowe. 
- wektory są bardzo długie
- brak różnicowania między lematami

## Zaproponuj procedur¦, która zawiera w sobie klasteryzacj¦ i dziaªa potencjalnie lepiej, ni» oryginalne reprezentacje (dodatkowo zwracaj¡c wektory o mniejszej liczbie wymiarów).

1. Zastosuj algorytm klasteryzacji do reprezentacji wektorowych słów.
2. Dla każdego klastra oblicz reprezentanta (np. średni wektor).
3. Użyj reprezentantów klastrów jako nowych wektorów słów.
4. Opcjonalnie: zredukuj wymiarowość nowych wektorów za pomocą technik takich jak PCA.