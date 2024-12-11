## W poniższym programie występuje sytuacja wyścigu (ang. race condition) dotycząca dostępów do współdzielonej zmiennej «tally». Wyznacz jej najmniejszą i największą możliwą wartość.

```C
const int n = 50;
shared int tally = 0;

void total() {
    for (int count = 1; count <= n; count++)
        tally = tally + 1;
}

void main() { 
    parbegin(total(), total()); 
}
```

Najmniejsza wartość: 2 - dodawanie jest wykonywane w tym samym momencie
Największa wartość: 100 - dodawanie jest wykonywane na przemian

## Dyrektywa «parbegin» rozpoczyna współbieżne wykonanie procesów. Maszyna wykonuje instrukcje arytmetyczne wyłącznie na rejestrach – tj. kompilator musi załadować wartość zmiennej «tally» do rejestru, przed wykonaniem dodawania. Jak zmieni się przedział możliwych wartości zmiennej «tally», gdy wystartujemy k procesów zamiast dwóch?
minimum: 2
maksimum: 50k


## Odpowiedź uzasadnij pokazując przeplot, który prowadzi do określonego wyniku.
minimum: 
```plaintext
proces 1
=> %rax = tally (0); =====> %rax += 1; ==========> reszta iteracji -|
                            tally = %rax (1); 

proces 2
========> 49 wykonań pętli ============> %rax = tally (1) ========> %rax += 1;
                                                                    tally = %rax (2);
```
maksimum:
```plaintext
proces 1
=> tally++ (1) ====> tally++ (3) ========iteracje=====|>

proces 2
======> tally++ (2) ==========iteracje============> tally++ (100) ==|>
```
