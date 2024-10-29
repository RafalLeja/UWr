### Intencją autora poniższego kodu było użycie plików jako blokad międzyprocesowych. Istnienie pliku o podanej nazwie w systemie plików oznacza, że blokada została założona. Brak tegoż pliku, że blokadę można założyć. Niestety w poniższym kodzie jest błąd TOCTTOU2, który opisano również w [4, 39.17]. Zlokalizuj w poniższym kodzie wyścig i napraw go! Opowiedz jakie zagrożenia niesie ze sobą taki błąd.

```c
#include "csapp.h"
bool f_lock(const char *path) {
    if (access(path, F_OK) == 0)
        return false;

    (void)Open(path, O_EXCL|O_CREAT|O_WRONLY, 0700);
    return true;
}

void f_unlock(const char *path) {
    Unlink(path);
}
```

If O_EXCL is set  with  O_CREAT  and
       the  file already exists, open()	returns	an error.

If  O_EXCL  is
       set  and	 the last component of the pathname is a symbolic link,	open()
       will fail even if the symbolic link points to a non-existent name.