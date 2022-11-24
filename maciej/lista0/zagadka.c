#include <stdio.h>

/* Wartości jakiej funkcji oblicza poniższy program? 
 *      Autor: Marek Piotrów, Data: 1.10.2019
 */

int main(void)
{
    int n = 0;
    double x = 0.0, dx = 0, eps = 0;
    double y1, y2;

    while (n <= 0 || x <= 0.0) { 
        printf(u8"Podaj dwie liczby dodatnie: naturalną i rzeczywistą:\n");
        scanf("%d %lf", &n, &x);
    }

    while (eps <= 0.0) { 
        printf(u8"Podaj dokładność obliczeń(eps):\n");
        scanf("%lf", &eps);
    }

    while (dx <= 0.0) { 
        printf(u8"Podaj wartość przyrostu argumentów(dx):\n");
        scanf("%lf", &dx);
    }
    

    printf("    x           f(x)\n");
 
    for (int i = 0; i < n; i++) {
        y1 = x;
        y2 = y1 / 2;
        while (y1 - y2 > eps || y2 - y1 > eps) {
            y1 = y2;
            y2 = (y1 + x / y1) / 2;
        }
        printf("%0.8f    %0.8f\n", x, y2);
        x += dx;
    }
    return 0;       //f(x) = x^(1/2)
}
