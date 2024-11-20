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
```C
// memory descriptor
// opisuje pamięć procesu
struct mm_struct {
    pgd_t *pgd; // wskaźnik do struktury pgd_t
    struct vm_area_struct *mmap; // wskaźnik do struktury vm_area_struct
    ...
};

// page global directory
// wzkazuje na tablicę stron
typedef struct { unsigned long pgd; } pgd_t;


// virtual memory area
// opisuje obszar pamięci
struct vm_area_struct {
    struct mm_struct *vm_mm; // wskaźnik do struktury mm_struct
    unsigned long vm_start; // początek obszaru
    unsigned long vm_end; // koniec obszaru
    ...
};
```
[mm_struct](https://docs.huihoo.com/doxygen/linux/kernel/3.7/structmm__struct.html#abd50fb5aab94b9d23e8104e96be6e45a)
[pgd_t](https://docs.huihoo.com/doxygen/linux/kernel/3.7/structpgd__t.html)
[vm_area_struct](https://docs.huihoo.com/doxygen/linux/kernel/3.7/structvm__area__struct.html)

![alt text](image-1.png)

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

