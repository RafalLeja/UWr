```C
#include <stdint.h>

#define Q 6
#define ONE (1 << Q)

int16_t exponential_smoothing(int16_t x, int16_t s, uint16_t alpha) {
    return (alpha * x + (ONE - alpha) * s) >> Q;
}

int main() {
    float alpha_f = 0.75;  // wartość alfa zapisana w formacie float
    uint16_t alpha = (uint16_t)(alpha_f * ONE);  // konwersja do Q16
    int16_t s = x0 << Q;  // wartość początkowa s0 = x0
    int16_t x;  // kolejne wartości xi

    // pętla obliczająca wygładzone wartości s
    for (int i = 1; i < n; i++) {
        s = exponential_smoothing(x, s, alpha);
    }

    return 0;
}
```
W funkcji exponential_smoothing wykonywane jest działanie zgodnie z algorytmem wygładzania wykładniczego z wartościami stałoprzecinkowymi. Stała Q oznacza, ile bitów po przecinku zostanie zachowane w obliczeniach. Stała ONE to liczba 1 z dokładnością do Q bitów po przecinku.

W funkcji main zmienna alpha_f zawiera wartość stałej $α$ w formacie float, a zmienna alpha to ta sama wartość w formacie stałoprzecinkowym Q16. Zmienna s przechowuje wartość początkową s0 = x0 przesuniętą o Q bitów, a zmienna x to kolejne wartości xi. W pętli obliczane są kolejne wygładzone wartości s przy użyciu funkcji exponential_smoothing.

Warto zwrócić uwagę, że w tej implementacji zakładamy, że liczba x zawsze mieści się w zakresie od -1 do