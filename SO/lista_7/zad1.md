### Na podstawie [3, 49.1] wyjaśnij słuchaczom różnicę między odwzorowaniami plików w pamięć (ang. memory-mapped files) i odwzorowaniami pamięci anonimowej (ang. anonymous mappings). Jaką zawartością wypełniana jest pamięć wirtualna należąca do tychże odwzorowań?
- odwzorowanie plików w pamięci:
    - to zmapowanie obszaru jakiegoś pliku do pamięci wirtualniej procesu
    - moża dostać się do zawartości przez operacje na tych bajtach
    - strony są automatycznie ładowane z pliku
- odwzorowanie pamięci anonimowej:
    - mapowanie bez odpowiadającego pliku
    - jest wypełnione zerami
    - tak jakby odwzorowanie nieistniejącego pliku wypełnionego zerami

### Czym różni się odwzorowanie prywatne od dzielonego?
- odwzorowanie prywatne:
    - zmiany w odwzorowaniu nie są widoczne w pliku
    - zmiany są widoczne tylko w tym procesie
    - copy-on-write

- odwzorowanie dzielone:
    - zmiany w odwzorowaniu są widoczne w pliku
    - zmiany są widoczne w innych procesach

### Czy pamięć obiektów odwzorowanych prywatnie może być współdzielona?
- tak, przed zapisaniem pamięci, po zapisaniu pamięci jest kopiowana

### Czemu można tworzyć odwzorowania plików urządzeń blokowych w pamięć, a znakowych nie?
- bo urządzenia blokowe umożliwiają dostęp do dowolnego bloku, a urządzenia znakowe nie

