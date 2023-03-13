1. INT_MIN32                       ```(x > 0) || (x - 1 < 0)```
2. x != ?????111 || x == ?????1??   ```(x & 7) != 7 || (x << 29 < 0)```
3. 0x0000C000                       ```(x * x) >= 0```
4. tautologia                       ```x < 0 || -x <= 0```
5. INT_MIN                          ```x > 0 || -x >= 0```
6. 0                                ```(x | -x) >> 31 == -1```
7. tautologia całość rzutowana na (uint32_t) ```x + y == (uint32_t)y + (uint32_t)x```
8. ~x + 1 == -x => ~x + x -1  
```(uint32_t)x * (uint32_t)(~y) + (uint32_t)y * (uint32_t)x == (uint32_t)(-x)``` Wyciągnijmy więc (uint32_t)x przed nawias, dzięki czemu uzyskamy
```(uint32_t)(~y) + (uint32_t)y = UINT32T_MAX```

, a pomnożenie (uint32_t)x * UINT32T_MAX zwróci nam wartość UINT32T_MAX - (uint32_t)x, co jest równe wartości (uint32_t)(-x)  ```x * ~y + (uint32_t)y * (uint32_t)x == -x```

