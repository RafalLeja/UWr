Mamy
```math
t(k): f(x)= \frac{\Gamma(\frac{k+1}{2})}{\sqrt{k\pi} \Gamma(k/2)} \left( 1+\frac{x^2}{k} \right)^{-(k+1)/2} dx
```

Chcemy dystrybuante, czyli
```math
F(x) = \int_{-\infty}^{x} f(t) dt
```

może być zapisane jako
```math
F(x) = \int_{-\infty}^{0} f(t) dt + \int_{0}^{x} f(t) dt
```

wiemy że rozkład t(k) jest symetryczny, więc
```math
F(0) = \int_{-\infty}^{0} f(t) dt = 0.5
```

Zatem jeśli x > 0 to
```math
F(x) = 0.5 + \int_{0}^{x} f(t) dt
```

oraz jeśli x < 0 to
```math
F(x) = 0.5 - \int_{x}^{0} f(t) dt
```