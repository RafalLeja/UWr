## Chcemy rozszerzyć algorytm z poprzedniego zadania o obsługę kopiowania przy zapisie (ang. copy on write). W przestrzeni adresowej procesu utworzono odwzorowania prywatne segmentów pliku wykonywalnego ELF. Rozważmy kilkustronicowy segment danych D przechowujący sekcję «.data». Wiele procesów wykonuje ten sam program, zatem każdy może zmodyfikować dowolną stronę w swoim segmencie D. Co jądro przechowuje w strukturze «vm_area_struct» opisującej segment D, a w szczególności w polach «vm_prot» i «vm_flags»?
- vm_area_struct:
  - vm_start: początek segmentu
  - vm_end: koniec segmentu
  - vm_prot: prawa dostępu do segmentu
  - vm_flags: flagi segmentu
  - vm_page_prot: prawa dostępu do strony
  - vm_file: wskaźnik do pliku
  - vm_pgoff: przesunięcie w pliku
  
### Jak jądro zmodyfikuje «mm_struct::pgd» w trakcie pierwszego odczytu ze strony p należącej do D, a jak w trakcie późniejszego pierwszego zapisu do p?
- w trakcie pierwszego odczytu:
  - jądro utworzy nową stronę, skopiując zawartość strony z pliku
  - zmieni wpis w tablicy stron, aby wskazywał na nową stronę
  - zmieni prawa dostępu do strony na tylko do odczytu
- lub (jeśli mamy wiele procesów wykonujących ten sam program):
  - jądro odczyta z istniejącej strony

- w trakcie pierwszego zapisu:
  - jądro wprowadzi zmiany w istniejącej stronie
- lub (jeśli mamy wiele procesów wykonujących ten sam program):
  - jądro utworzy kopię strony
  - zmieni wpis w tablicy stron, aby wskazywał na nową stronę

### Co jądro musi zrobić z tablicą stron procesu, który zawołał fork(2)?
- jądro musi utworzyć kopię tablicy stron procesu rodzica dla procesu potomnego
- jądro musi zaznaczyć wszystkie strony jako tylko do odczytu
- po pierwszym zapisie do strony, jądro utworzy kopię strony
  