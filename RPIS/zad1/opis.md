# Zadanie nr 1
Rafał Leja 340879 01.04.2025

340879 mod 4 = 3

## Zadanie 3, rozkład t-studenta

### 1. Liczenie dystrybuanty

Mamy gęstość rozkładu t-studenta, podaną jako
$$
t(k): f(x)= \frac{\Gamma(\frac{k+1}{2})}{\sqrt{k\pi} \Gamma(k/2)} \left( 1+\frac{x^2}{k} \right)^{-(k+1)/2} dx
$$

Chcemy obliczyć dystrybuante, czyli
$$
F(x) = \int_{-\infty}^{x} f(t) dt
$$

co może być zapisane jako
$$
F(x) = \int_{-\infty}^{0} f(t) dt + \int_{0}^{x} f(t) dt
$$

wiemy że rozkład t(k) jest symetryczny względem zera, więc
$$
F(0) = \int_{-\infty}^{0} f(t) dt = 0.5
$$

Zatem jeśli x > 0 to
$$
F(x) = 0.5 + \int_{0}^{x} f(t) dt
$$

oraz jeśli x < 0 to
$$
F(x) = 0.5 - \int_{x}^{0} f(t) dt
$$

### 2. Numeryczna poprawność funkcji Gammma


Funkcja gamma jest zdefiniowana jako
$$
\Gamma(x) = \int_{0}^{\infty} t^{x-1} e^{-t} dt
$$

Co jest równoważne
$$
\Gamma(x) = x * \Gamma(x-1)\quad  \text{dla} \quad  x \in \mathbb{N}
$$

Na nasze szczęście w tym zadaniu liczymy funcję gamma dla $\frac{k}{2}$ dla $k \in \mathbb{N}$, więc możemy użyć własności rekurencyjnej funkcji gamma, oraz faktu że funkcja gamma przyjmuje wartości:
$$
\Gamma(1/2) = \sqrt{\pi} \\
\Gamma(1) = 1
$$
W ten sposób mamy prostą numerycznie poprawną funkcję gamma, która nie wymaga obliczania całek.

### 3. Metoda trapezów

Metoda trapezów jest jedną z najprostszych metod numerycznych do obliczania całek. Polega na przybliżeniu funkcji linią prostą i obliczeniu pola trapezu. Możemy to zapisać jako
$$
\int_{a}^{b} f(x) dx \approx \frac{(b-a)}{2} (f(a) + f(b))
$$
dla jednego przedziału, lub
$$
\int_{a}^{b} f(x) dx \approx \frac{(b-a)}{2} (f(a) + f(b)) + 2f(x_1) + 2f(x_2) + \ldots + 2f(x_{n-1})
$$
gdzie $x_i$ to punkty podziału przedziału $[a,b]$ na n równych części.

### 5. Metoda Romberga
Metoda Romberga jest bardziej zaawansowaną metodą numeryczną do obliczania całek. Polega na iteracyjnym poprawianiu wyniku metody trapezów, aż do osiągnięcia zadowalającej dokładności. Możemy to zapisać jako
$$
\begin{cases}
R_{0,i} = \text{metoda trapezów na } 2^i \text{ przedziałach} \\
R_{k,i} = \frac{4^k R_{k-1,i+1} - R_{k-1,i}}{4^k - 1}
\end{cases}
$$
gdzie $R_{k,i}$ to wynik metody Romberga dla k-tej iteracji i i-tego podziału. Metoda Romberga jest bardziej skomplikowana, ale daje lepsze wyniki niż metoda trapezów.

### Zakończenie

Używając powyższych metod, możemy obliczyć dystrybuantę rozkładu t-studenta dla dowolnej liczby stopni swobody k.