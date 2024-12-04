## Na podstawie [6, 1.5] wyjaśnij zadania pełnione przez protokoły warstwy: łącza, sieciowej i transportowej.

- Warstwa transportowa:
    - dwa główne protokoły:
      - TCP (Transmission Control Protocol) - zapewnia niezawodność transmisji, kontrolę przepływu, kontrolę błędów i segmentację danych
      - UDP (User Datagram Protocol) - zapewnia jedynie podstawową funkcjonalność, tj. przesyłanie datagramów bez potwierdzeń, bez kontroli przepływu i bez segmentacji danych
    - protokoły te są odpowiedzialne za komunikację między procesami użytkownika na różnych hostach

- Warstwa sieciowa:
    - tylko jeden główny protokół:
      - IP (Internet Protocol) - zapewnia adresowanie i trasowanie pakietów między hostami
      - protokół ten jest odpowiedzialny za komunikację między hostami w sieci
    - służy do przesyłania pakietów między hostami w sieci

- Warstwa łącza:
    - wiele protokołów:
      - Ethernet - zapewnia dostarczenie ramek do warstwy sieciowej
      - PPP (Point-to-Point Protocol) - zapewnia dostarczenie ramek do warstwy sieciowej
      - Wi-Fi - zapewnia dostarczenie ramek do warstwy sieciowej
    - służy do przesyłania ramek między węzłami w sieci.

## Zainstaluj i uruchom program wireshark1. Przechwyć kilka pakietów protokołów UDP i TCP, a następnie wytłumacz do czego służy kapsułkowanie (ang. encapsulation) i wyświetl (tj. kliknij dwukrotnie na pakiet) nagłówki ramki, datagramu i segmentu. Zidentyfikuj adres źródłowy i docelowy pakietu.

- Kapsułkowanie (encapsulation) polega na dodawaniu nagłówków i/lub stopki do danych, które są przesyłane przez sieć. Nagłówki i stopki zawierają informacje, które są niezbędne do przesłania danych z jednego węzła do drugiego. W przypadku protokołów TCP i UDP, dane są kapsułkowane w segmenty/datagramy, które są przesyłane przez sieć. W przypadku protokołu Ethernet, dane są kapsułkowane w ramki, które są przesyłane przez sieć.


## Czemu protokoły warstwy łącza i sieciowej nie są używane do komunikacji między procesami użytkownika?

warstwa łącza nie zna procesów, i potrafi tylko przesłać dane między węzłami w sieci.

adresy ip używanie w warstwie sieciowej są adresami hostów, a nie procesów, więc nie można ich używać do komunikacji między procesami użytkownika.
