## Zadanie 1

### Znajdź informacje o wielkoóci modelu GPT-3. Przyjmijmy założenie, że cyfra=token, mnożenie jest realizowane na sekwencyjnym, jednowątkowym procesorze, a do mnożenia macierzy używamy szkolnego algorytmu O(N3). Jak wiele operacji mnożenia musi wykonać transformer GPT-3, żeby pomnożyć dwie liczby trzycyfrowe, większe od 400. Wynik nie musi być dokładny, możesz pomylić się o rząd, czy dwa.

Zał że wejście to "400*401", N = 7

1. Zanurzenie:
    - (N x 50257) * (50257 x 12288) => 126937424324593 | 4,322,906,112
2. Pojedyńcze 'query':
    - (N x 12288) * (12288 x 128) => 1855425871872 = Q | 11,010,048
3. Atencja dla N tokenów:
    - 3x Q * N * N = 272,747,603,165,184 | 1618477056
4. 96 głowic:
    - 96 x 272,747,603,165,184 = 26,183,769,903,857,664 | 155,373,797,376
5. Feedforward:
    - (N x 12288) * (12288 x 49152) * (49152 x 12288) = 237494511599616 | 7,425,931,345,920
5. 96 warstw:
    - 96 x (237494511599616 + 26,183,769,903,857,664) = 2,536,441,383,883,898,880 | 7,581,305,143,296
6. Wynurzenie:
    - (N x 12288) * (12288 x 50257) = 126937424324593 | 4,322,906,112
7. Suma:
    - 2,536,695,258,732,548,066 = 2.5e18 | 7,589,950,955,520

## Zadanie 2 Na jakich zbiorach danych trenuje się modele wymienione na stronie HuggingFace w grupie Table Question Answering. W zadaniu należy się posłużyć informacjami, jakie dają twórcy najbardziej popularnych modeli w danej klasie.

na tabelach z Wikipedii, oraz zapytaniach SQL

## Zadanie 3 Na jakich zbiorach danych trenuje się modele wymienione na stronie HuggingFace w grupie Zero-Shot Classification.

Na zbiorach danych zawierających zdanie, oraz etykietę klasy.

## Zadanie 4 Wybierz jakąó grę planszową, w której rzucane są koóci (na przykład chiśczyka czy tryktraka, możesz posiłkować się też listą https://en.wikipedia.org/wiki/List_of_dice_games) Jak napisać agenta, grającego w tę grę, używając autoregresywnego modelu językowego. Czy użycie koóci wprowadza tu jakąś komplikację, a jeżeli tak, to jak ją najlepiej rozwiązać?

### Gra: Chińczyk

### Agent w Chińczyku ma za zadanie tylko wybrać 1 z 4 pionków, które chce ruszyć. Wartość kości jest jedynie informacją, która z pionków jest dostępna do ruchu. Jeśli agent obierze taktykę że zawsze rusza najdalszym pionkiem, może nastąpić problem przy końcu gry, kiedy pionki są już blisko mety. Wtedy agent może zaczynać ruszać pionkami, które są już blisko mety, co jest nieefektywne. Rozwiązaniem tego problemu może być przekazywanie agentowi wartości kości.
