## Definicje:
- Profilowanie:
  - Uruchamianie programu z dodatkowymi funkcjami liczącymi czas wykonywania konktretnych części programu
- Profil płaski:
  - lista wszystkich funkcji wykonanych podczas uruchamiania programu, z czasem wykonywania oraz ilością wywołań
- Graf wywołań funkcji
   - skierowany graf ilustrujący kolejność wywoływanych funkcji i relację między funkcjami wyłowującymi, a wywołanymi.
 - Zliczanie interwałowe
   - pobieranie danych o programie w stałych interwałach czasu programu. Pozwala wyeliminować błędy obliczeń wywołane przez np. I/O lub inne programy


### W jakim celu profiluje się programy?
 - w celu uzyskania wskazówek do optymalizacji

### Jakie informacje niesie ze sobą profil płaski [ 2, 5.1] i profil grafu wywołań [2 , 5.2]?
 - czas wywołań fukncji, skąd są wywoływane, ile razy są wywoływane

### Czemu profilowanie programu wymaga zbudowania go ze specjalną opcją kompilatora «-pg»?
  - flaga -pg dodaje do programu kod odpowiedzialny za wypisywanie profilu
  