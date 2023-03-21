```0 01111 10010000000```
{x} <= znak
{5x} <= wykładnik
{11x} <= mantysa

skoro wykładnik ma 5 bitów i jest bez znaku to zakres to <0, 32>

00000 jest zarezerwowane przez 0 gdy matysa = 0 i liczby subnormalne
11111 jest zarezerwowane przez inf gdy mantysa = 0 i NaN

więc żeby uzyskać zakres <-14, 15> musimy odejmować 15 od liczby wykładnika

# 16 bit:
 - |max| = 6.55 * 10^4
 - |min| = - 6.10 * 10^-5
 - dokładność = 5.96 * 10^-8

# 32 bit:
- |max| = 3.4028 * 10^38
- |min| = 1.1754 ⋅ 10^−38
- dokładność = 1.18 * 10^-38 = 2^-126
- subnormal = 1.4012*10^-45