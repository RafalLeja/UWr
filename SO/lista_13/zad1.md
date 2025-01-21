### Przypomnij z wykładu na czym polega problem odwrócenia priorytetów oraz metodę jego rozwiązywania o nazwie dziedziczenie priorytetów?


- odwrócenie priorytetów:
    - proces H oraz L (H > L) wykonujący operacje na wspólnym zasobie
    - jeśli L zablokuje zasób, to w normalnej sytuacji L możliwie szybko zwolinło by zasób
    - jeśli w trakcie wykonywania L, proces M (H > M > L) wywłaszczy proces L,
    to w rzeczywistości zablokuje również proces H co jest sprzeczne z ich piorytetami

- dziedziczenie piorytetów:
    - jeśli jakiś wysokopiorytetowy proces czeka na zwolnienie zasobu przez inny, niskopiorytetowy proces to tymczasowo zwiększamy piorytet drugiego procesu, żeby nie został wywłaszczony

- mutex (mutual exeption):
    - "zamek" który ogranicza dostęp do zasobu do pojedyńczego wątku

### W jakim celu mutex pamięta właściciela, tj. wątek który trzyma blokadę?

- żeby wiedzieć kto może go zwolnić

### W jaki sposób należy rozszerzyć implementację operacji «mutex_lock» i «mutex_unlock», żeby nie dopuścić do odwrócenia priorytetów?

```C

int lock(mutex_t *mutex){
    if (mutex->id) > 0 {
        // mutex zablokowany
        if (getPri(getpid()) > getPri(mutex->id)){
            setPri(mutex->id, getPri(getpid())
        }
    } else {
        ...
    }
}

int unlock(mutex_t *mutex){
    setPri(getpid(), 0) // reset
    ...
}
```
### Czy semafory są odporne na problem odwrócenia priorytetów?

- domyślnie nie 

