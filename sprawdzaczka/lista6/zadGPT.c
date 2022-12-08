#include <stdio.h>

int main()
{
int n;
printf("Podaj wymiar klejki (n x n): ");
scanf("%d", &n);

int liczba_dziur = n*n; // liczba płatów w klejce

// jeśli n jest nieparzyste, to po obróceniu płatów dziura zawsze będzie widoczna
if (n % 2 == 1)
{
    printf("Liczba dziur na wylot: %d", liczba_dziur);
    return 0;
}

// jeśli n jest parzyste, to po obróceniu płatów dziura będzie widoczna tylko wtedy, gdy obrócimy płat o 90 lub 270 stopni
// dla tego przypadku mamy 4 możliwe układy:
// 1. wszystkie płaty obrócone o 0 stopni
// 2. wszystkie płaty obrócone o 90 stopni
// 3. wszystkie płaty obrócone o 180 stopni
// 4. wszystkie płaty obrócone o 270 stopni
// dla układu 1. i 3. dziura nie będzie widoczna, dla układów 2. i 4. dziura będzie widoczna
liczba_dziur /= 2; // dla każdego układu 2. i 4. dziura będzie widoczna
printf("Liczba dziur na wylot: %d", liczba_dziur);

return 0;
}