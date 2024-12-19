## Korzystając z pól superbloku (ang. superblock) podaj wzór na wyliczenie wartości: rozmiaru bloku, liczby i-węzłów i bloków przechowywanych w grupie bloków (ang. block group), liczby wpisów tablicy deskryptorów grup bloków (ang. block group descriptor table).

- Rozmiar bloku: `1024 * 2^superblock.s_log_block_size`
- Liczba i-węzłów w grupie: `superblock.s_inodes_per_group`
- Bloków przechowywanych w grupie bloków: `superblock.s_blocks_per_group`
- Liczba wpisów tablicy deskryptorów grup bloków: `ceil(superblock.s_blocks_count / superblock.s_blocks_per_group)`

## Wymień składowe należące do grupy bloków oraz podaj ich rozmiar w blokach.


## Które grupy bloków przechowują kopie zapasową superbloku i tablicy deskryptorów grup bloków?