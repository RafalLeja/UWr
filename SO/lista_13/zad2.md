### Podaj implementację (w języku C) semafora z operacjami «init», «wait» oraz «post» używając wyłącznie muteksów i zmiennych warunkowych standardu POSIX.1. Pamiętaj, że wartość semafora musi być zawsze nieujemna.

```C

typedef struct Sem {
    int value;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}

void init(Sem *sem, int value){
    sem->value = value;
    pthread_mutex_init(&sem->mutex, NULL);
    pthread_cond_init(&sem->cond, NULL);
}

// P
void wait(Sem *sem){
    pthread_mutex_lock(&sem->mutex);
    
    while (sem->value <= 0){
        pthread_cond_wait(&sem->cond, &sem->mutex);
    }
    
    sem->value--;
    
    pthread_mutex_unlock(&sem->mutex);
}

// V
void post(Sem *sem){
    pthread_mutex_lock(&sem->mutex);
    
    sem->value++;
    
    pthread_cond_signal(&sem->cond);
    
    pthread_mutex_unlock(&sem->mutex);
}

```

