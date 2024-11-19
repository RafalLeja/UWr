### Na podstawie slajdów do wykładu opisz algorytm obsługi błędu stronicowania w systemie Linux.
- jądro przechodzi po obszarach, sprawdzając który miał być odczytany, jeśli mamy prawo i istnieje strona to ją wczytujemy

### Jakie informacje musi dostarczyć procesor, żeby można było wykonać procedurę obsługi błędu stronicowania? Do czego służą struktury jądra «mm_struct::pgd» i «mm_struct::mmap» zdefiniowane w pliku include/linux/mm_types.h?
- procesor musi dostarczyć:
    - fault_addr: adres błędu
    - fault_pc: instrukcja, która spowodowała błąd
    - fault_size: rozmiar operacji
    - fault_prot: prawa dostępu

- mm_struct::pgd: zawiera wskaźnik do tablicy stron:
- mm_struct::mmap: zawiera informacje o mapowaniu pamięci

### Kiedy jądro wyśle procesowi sygnał SIGSEGV z kodem «SEGV_MAPERR» lub «SEGV_ACCERR»?
- SIGSEGV z kodem SEGV_MAPERR jest wysyłany, gdy proces próbuje odwołać się do adresu, który nie jest zmapowany
- SIGSEGV z kodem SEGV_ACCERR jest wysyłany, gdy proces próbuje odwołać się do adresu, do którego nie ma uprawnień

### W jakiej sytuacji wystąpi pomniejsza usterka strony (ang. minor page fault) lub poważna usterka strony (ang. major page fault)?
- pomniejsza usterka:
    - strona jest w pamięci, ale jej wpis w tablicy stron nie jest oznaczony jako obecny
    - np. inny proces mógł ją usunąć
- poważna usterka:
    - strona nie jest w pamięci wirutalnej
    - np. strona nie została jeszcze wczytana z dysku

### Jaką rolę pełni w systemie bufor stron (ang. page cache)?
- bufor cachuje strony, które były wczytywane z dysku, pozwalając na szybszy dostęp do nich

