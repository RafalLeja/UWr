1. (float)x == (float)dx T taka sama strata przy konwersji
2. dx - dy == (double)(x - y) F jeżeli (x - y) < INT_MIN
3. (dx + dy) + dz == dx + (dy + dz) T zapas bitów
4. (dx * dy) * dz == dx * (dy * dz) -||-
5. dx / dx == dz / dz T gdy dx i dz =! 0