## Czym różni się przetwarzanie równoległe (ang. parallel) od przetwarzania współbieżnego (ang. concurrent)? 
- Równoległe:
    - wiele różnych zadań wykonywanych jednocześnie
    - wymaga wielu procesorów
- Współbieżne:
    - wiele różnych zadań naprzemiennie
    - wymaga jednego procesora

## Czym charakteryzują się procedury wielobieżne (ang. reentrant)?
- Procedura wielobieżna:
    - może zostać przerwana i wznowiona w dowolnym momencie
    - dane i zmienne nie mogą być zmieniane przez inne wątki
    - nie może używać procedur niewielobieżnych

## Podaj przykład procedury w języku C (a) wielobieżnej, ale nie wielowątkowo-bezpiecznej (ang. MT-safe) (b) na odwrót.
- a) Procedura wielowątkowo-bezpieczna, ale nie wielobieżna:
```C
int tmp;

void swap(int* x, int* y)
{
    tmp = *x;
    *x = *y;
    *y = tmp;
}
```

- b) Procedura nie wielobieżna, ale wielowątkowo-bezpieczna:
```C
_Thread_local int tmp;

void swap(int* x, int* y)
{
    tmp = *x;
    *x = *y;
    /* isr() */
    *y = tmp;    
}

void isr()
{
    int x = 1, y = 2;
    swap(&x, &y);
}
```

## Kiedy w jednowątkowym procesie uniksowym może wystąpić współbieżność?
Jeśli proces wywołuje funkcje systemowe