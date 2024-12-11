## Podaj procedury wątków POSIX, które pełnią podobną funkcję co fork(2), exit(3), waitpid(2), atexit(3) oraz abort(3) na procesach. Opisz semantykę podanych funkcji i powiedz gdzie się różnią od swoich odpowiedników na procesach.
```C
fork()

int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                   void *(*start_routine) (void *), void *arg);

exit()

void pthread_exit(void *retval);

waitpid()

int pthread_join(pthread_t thread, void **retval);

atexit()

void pthread_cleanup_push(void (*routine)(void *),
                                 void *arg);

getpid()

pthread_t pthread_self(void);

abort()

void pthread_cancel(pthread_t thread);

```


## Porównaj zachowanie wątków złączalnych (ang. joinable) i odczepionych (ang. detached).
- Złączalne:
    - nie zwalniają zasobów po zakończeniu wątku
    - trzeba je pogrzebać za pomocą pthread_join
- Odczepione:
    - zasoby są zwalniane po zakończeniu wątku
    - nie można ich grzebać

## Zauważ, że w systemie Linux procedura pthread_create odpowiada za utworzenie reprezentacji wątku w przestrzeni użytkownika, w tym utworzenie stosu i uruchomienie wątku przy pomocy wywołania clone(2). Kto zatem odpowiada za usunięcie segmentu stosu z przestrzeni użytkownika, gdy wątek złączalny albo odczepiony zakończy pracę? Pomocne może być zajrzenie do implementacji funkcji pthread_exit, pthread_join i __unmapself.

```plaintext
man pthread_join

After  a  successful  call  to pthread_join(), the caller is guaranteed that the target thread has terminated.
The caller may then choose to do any clean-up that is required after termination of the thread (e.g.,  freeing
memory or other resources that were allocated to the target thread).
```

- Złączalne:
    - pthread_join
- Odczepione:
    - pthread_exit za pomocą __unmapself