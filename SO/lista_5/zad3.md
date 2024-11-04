## W systemach uniksowych katalog to ciąg bajtów reprezentujący listy rekordów dirent(3). Na podstawie [3, rysunek 10-32] przedstaw reprezentację katalogu, a następnie wyjaśnij jak przebiegają operacje usuwania i dodawania pliku. W pierwszym przypadku rozważ scenariusz, w którym w reprezentacji katalogu za lub przed usuwanym wpisem istnieją nieużytki. W drugim, kiedy w pliku katalogu nie udaje się znaleźć wystarczająco dużo miejsca na przechowanie wpisu.

![linux file system](image-2.png)

 - Usuwanie pliku:
   1. zmieniamy rozmiar rekordu w poprzednim wpisie
 - Dodawanie pliku:
   1. szukamy miejsca na nowy wpis
   2. jeśli nie ma wystarczająco dużo miejsca, to:
        1. dodajemy nowy blok
        2. kompaktujemy katalog
   3. dodajemy nowy wpis

### Jądro leniwie wykonuje operację kompaktowania na katalogach – kiedy opłaca się ją zrobić?
kiedy z katalogu o wielu plikach usuwamy wiele plików