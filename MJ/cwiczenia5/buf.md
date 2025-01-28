## Zadanie 1

### Znajdź informacje o wielkoóci modelu GPT-3. Przyjmijmy założenie, że cyfra=token, mnożenie jest realizowane na sekwencyjnym, jednowątkowym procesorze, a do mnożenia macierzy używamy szkolnego algorytmu O(N3). Jak wiele operacji mnożenia musi wykonać transformer GPT-3, żeby pomnożyć dwie liczby trzycyfrowe, większe od 400. Wynik nie musi być dokładny, możesz pomylić się o rząd, czy dwa.

Zał że wejście to "400*401", N = 7

1. Zanurzenie:
    - (N x 50257) * (50257 x 12288) => 126937424324593 
2. Pojedyńcze 'query':
    - (N x 12288) * (12288 x 128) => 1855425871872 = Q
3. Atencja dla N tokenów:
    - 3x Q * N * N = 272,747,603,165,184
4. 96 głowic:
    - 96 x 272,747,603,165,184 = 26,183,769,903,857,664
5. Feedforward:
    - (N x 12288) * (12288 x 49152) * (49152 x 12288) = 237494511599616
5. 96 warstw:
    - 96 x (237494511599616 + 26,183,769,903,857,664) = 2,536,441,383,883,898,880
6. Wynurzenie:
    - (N x 12288) * (12288 x 50257) = 126937424324593
7. Suma:
    - 2,536,695,258,732,548,066 = 2.5e18