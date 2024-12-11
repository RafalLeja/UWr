## Wybierz odpowiedni scenariusz zachowania wątków, w którym konkurują o dostęp do zasobów, i na tej podstawie precyzyjnie opisz zjawisko zakleszczenia (ang. deadlock),
- Wątek A:
    - zablokuj zasób 1
    - zablokuj zasób 2
    - zmień zasób 1 i 2
    - odblokuj zasób 1
    - odblokuj zasób 2
- Wątek B:
    - zablokuj zasób 2
    - zmień zasób 2
    - odblokuj zasób 2
    - zablokuj zasób 1
    - zmień zasób 1
    - odblokuj zasób 1

## uwięzienia (ang. livelock)
- Wątek A:
    - zablokuj zasób 1 jeśli się nie da to zablokuj zasób 2
    - ...
- Wątek B:
    - zablokuj zasób 2 jeśli się nie da to zablokuj zasób 1
    - ...

## oraz głodzenia (ang. starvation).
- Wątek 1-1000 z piorytetem 1:
    - zablokuj zasób 1
    - ...
- Wątek 1001 z piorytetem 0:
    - zablokuj zasób 1