## Bufor TLB
-  (ang. translation lookaside buffer) (czasami pamięć asocjacyjna) to rodzaj pamimięci podręcznej służący do odwzorowywania adresów wirtualnych na fizyczne bez konieczności sięgania do tabeli stron. Zwykle jest ono zlokalizowane wewnątrz jednostki MMU i składa się z niewielkiej liczby pozycji - każda pozycja zawiera informacje dotyczące jednej strony, obejmują one numer strony wirtualnej (VPN), bit ustawiany w przypadku gdy strona jest zmodyfikowana, kod zabezpieczenia (uprawnienia czytania/pisania/uruchamiania) oraz fizyczną ramkę strony wskazującą na lokalizację strony w pamięci fizycznej. Pola te odpowiadają jeden do jednego polom w tabeli stron, wyjątkiem jest numer strony wirtualnej, który nie jest potrzebny w tabeli stron. Kolejny bit wskazuje na to, czy pozycja jest ważna (tzn. czy jest w użyciu), czy nie.

## Czemu dodanie TLB (ang. translation lookaside buffer) do jednostki zarządzania pamięcią (ang. memory management unit) przyspiesza translację adresów?

  Dodanie TLB (Translation Lookaside Buffer) do jednostki zarządzania pamięcią (MMU) przyspiesza translację adresów poprzez wprowadzenie mechanizmu buforowania tłumaczeń stron pamięci wewnątrz jednostki. TLB jest specjalnym rodzajem pamięci podręcznej, która przechowuje często używane tłumaczenia adresów w postaci par (adres wirtualny, adres fizyczny). Dzięki temu, zamiast przeprowadzać pełne tłumaczenie adresu za każdym razem, MMU może najpierw sprawdzić TLB. Jeśli tłumaczenie jest obecne w TLB, to od razu otrzymuje się odpowiadający mu adres fizyczny, co przyspiesza dostęp do pamięci.

## W jaki sposób różni się adresowanie TLB od adresowania pamięci podręcznej procesora?
 
Adresowanie TLB różni się od adresowania pamięci podręcznej procesora. Pamięć podręczna procesora to pamięć wykorzystywana do przechowywania często używanych danych lub instrukcji w celu przyspieszenia operacji odczytu/zapisu. Adresowanie pamięci podręcznej procesora odbywa się na podstawie adresów fizycznych lub wirtualnych (w przypadku pamięci podręcznej wirtualnej). Natomiast TLB tłumaczy adresy wirtualne na adresy fizyczne, co jest niezbędne w przypadku, gdy procesor korzysta z mechanizmu pamięci wirtualnej.

## Kiedy ładowanie wpisu tablicy stron do TLB zakończy się wygenerowaniem wyjątku procesora?

Ładowanie wpisu tablicy stron do TLB może zakończyć się wygenerowaniem wyjątku procesora w przypadku, gdy dany wpis nie istnieje w TLB. W takiej sytuacji MMU musi przeprowadzić pełne tłumaczenie adresu i załadować nowy wpis do TLB. Może to prowadzić do wyjątków, takich jak wyjątek braku strony (ang. page fault) lub inne wyjątki związane z błędami w tablicach stron.

## Czemu procesory używają osobnych TLB do tłumaczenia adresów instrukcji i danych? 

Procesory używają osobnych TLB do tłumaczenia adresów instrukcji i danych, ponieważ w przypadku pamięci wirtualnej programy często posiadają osobne obszary adresowe dla kodu (instrukcji) i danych. Oddzielne TLB dla instrukcji i danych pozwala na efektywną obsługę tych dwóch rodzajów dostępów, poprawiając wydajność i unikając konfliktów w buforze TLB.

cpuid -l 2