## Przestrzeń adresowa
 - zbiór możliwej do zaadresowania przez proces pamięci. Nie cały jej obszar musi mieć swój odpowiednik w pamięci fizycznej, co jest implementowane za pomocą pamięci wirtualnej.

## Pamięć wirtualna
-  działa na zasadzie przedefiniowania adresów pamięci (fizycznych) na adresy używane przez procesy (adresy wirtualne) tak, aby “oszukać” procesy i dać im wrażenie pracy w ciągłej przestrzeni adresowej. Pamięć wirtualna oznacza znacznie większą ilość pamięci RAM dla procesu niż fizycznie dostępna w systemie.

## Stronicowanie 
 - jeden ze sposobów rozwiązania problemu zewnętrznej fragmentacji, polegający na dopuszczeniu nieciągłości rozmieszczenia logicznej przestrzeni adresowej procesu w pamięci fizycznej. Pamięć fizyczna dzielona jest na bloki stałej długości zwane ramkami. Pamięć logiczna dzielona jest na bloki stałej długości zwane stronami. Rozmiary stron i ramek są identyczne.

## Tablica stron
- służy do odwzorowania stron wirtualnych na strony fizyczne. Z matematycznego punktu widzenia tabela stron jest funkcją, w której numer wirtualnej strony stanowi argument, a numer strony fizycznej - wynik. Dzięki wykorzystaniu wyniku tej funkcji można zastąpić pole numeru strony w adresie wirtualnym polem ramki strony i w ten sposób utworzyć adres w pamięci fizycznej.

## Wpis tablicy stron
 - to rekord tablicy stron, VPN, PPN(część adresu fizycznego) oraz bit valid.

## Stronicowanie dwupoziomowe 
- metoda oszczędzania pamięci, gdzie tablica stron sama podzielona jest na strony.

## Procesor posługuje się 32-bitowymi adresami wirtualnymi, rozmiar strony ma 4KiB, katalog tablicy stron ma 1024 wpisy, a rozmiar wpisu tablicy stron zajmuje 4 bajty. Dalej rozważamy proces, który łącznie używa 1GiB swojej wirtualnej przestrzeni adresowej. Podaj maksymalny i minimalny rozmiar tablicy stron (a) jednopoziomowej oraz (b) dwupoziomowej.

32-bitowe adresy wirtualne
page size: 4 KB = 4096 bajt = 2^12
wpis tablicy stron zajmuje: 4 bajty = 2^2
rozmiar przestrzeni adresowej 1GB = 2^30 bajt

rozmiar tablicy stron:
(a) jednopoziomowej

2^30/2^12
(rozmiar_adresu / rozmiar_strony) = 2^18 stron 
Każdy wpis zajmuje 4 bajty więc rozmiar tablicy stron jest równy 2^18*4=1MB

(b) dwupoziomowej, gdzie katalog tablicy stron ma 1024 wpisy
MAX
Każda strona drugiego poziomu może mapować maksymalnie 2^10*2^12=2^22
bajt (liczba_wpisów * page_size)
2^32/2^622=2^10=1024 liczba stron drugiego poziomu.
1024+1(jedna strona 1 poziomu) = 1025*4=4MB+4KB

MIN
Ponieważ potrzebujemy tylko 1GB przestrzeni, pozostałe 3GB nie musimy mapować i możemy zostawić ich jako puste wpisy w tablice 1 poziomu:
2^30/2^2=2^8=256
liczba stron drugiego poziomu.
256+1(jedna stron 1 poziomu) = 257*4=1MB+4KB