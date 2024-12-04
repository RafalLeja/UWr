## Na podstawie [7, 2.3 i 2.4] omów różnice między protokołami warstwy transportowej: datagramowym udp(7) i połączeniowym tcp(7).

- UDP:
    - prosty i bezpołączeniowy
    - używa mało informacji sterujących
- TDP:
    - niezawodny
    - strumieniowy
    - full-duplex
    - pakiety są dostarczane w kolejności, a utracone są wysyłane ponownie

## Czym różni się komunikacja półdupleksowa od dupleksowej?

- półdupleks:
    - albo odbiór albo wysyłka

- full-dupleks:
    - wysyłka i odbiór naraz

## Jak TCP radzi sobie z zagubieniem segmentu lub faktem, że segmenty mogą przyjść do odbiorcy w innej kolejności niż zostały wysłane?

TCP wysyła ponownie segmenty które nie były odebrane przez odbiorce, oraz ustawia segmenty w takiej kolejności w jakiej były wysłane

## Skąd protokół TCP wie kiedy połączenie zostało zerwane?

jeśli odbiorca nie daje znać że coś odbiera

## Jaki problem rozwiązuje sterowanie przepływem (ang. flow control) implementowane przez TCP?

flow control zapobiega przepełnieniu bufora gniazda. Gdy bufor się zapełnia TCP informuje dostawce o tym żeby wysyłał wolniej, lub żeby zatrzymał wysyłanie
