### Wyjaśnij różnicę między fragmentacją wewnętrzną i zewnętrzną.
- fragmentacja wewnętrzna: niewykorzystana część pamięci wewnątrz bloku pamięci, służy jako dodatkowa informacja o np. rozmiarze bloku
- fragmentacja zewnętrzna: niewykorzystana część pamięci pomiędzy blokami pamięci, występuje z powodu alokacji i dealokacji bloków o różnych rozmiarach

### Czemu algorytm malloc nie można stosować kompaktowania?
ponieważ zmieniłby on adresy bloków pamięci, co mogłoby prowadzić do błędów w programie

### Na podstawie [6, §2.3] opowiedz o dwóch głównych przyczynach występowania fragmentacji zewnętrznej.
- izolowana śmierć: jeśli blok znajduje się między dwoma innymi zaalokowanymi blokami, może nigdy nie zostać użyty
- zachowania czasowo-zależne: programy często alokują wiele bloków podobnych rozmiarów, po czym je zwalniają i alokują nowe o innych rozmiarach, co prowadzi do powstawania dziur 