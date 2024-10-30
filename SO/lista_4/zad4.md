### Przyjrzyjmy się raz jeszcze plikowi «pipeline.log» z poprzedniego zadania. Zauważ, że wszystkie procesy należące do potoku muszą zostać umieszczone w jednej grupie procesów. Wskaż kiedy powłoka tworzy nową grupę procesów i jak umieszcza tam procesy realizujące potok.
```bash
38982 setpgid(38995, 38994)             = 0
38995 setpgid(0, 38994)                 = 0

```
### Przeczytaj [2, 34.2] i wyjaśnij czemu dla każdego podprocesu wywołanie setpgid(2) jest robione zarówno w procesie powłoki jak i w procesie potomnym?
```C
case 0: /* Child */
    if (setpgid(0, pipelinePgid) == -1)
        /* Handle error */
    /* Child carries on to exec the required program */
default: /* Parent (shell) */
    if (setpgid(childPid, pipelinePgid) == -1 && errno != EACCES)
        /* Handle error */
    /* Parent carries on to do other things */
```

because the scheduling of the parent and
child is indeterminate after a fork() (Section 24.4), we can’t rely on the parent changing
the child’s process group ID before the child does an exec(); nor can we rely on the
child changing its process group ID before the parent tries to send any job-control
signals to it. (Dependence on either one of these behaviors would result in a race condition.) Therefore, job-control shells are programmed so that the parent and the
child process both call setpgid() to change the child’s process group ID to the same
value immediately after a fork(), and the parent ignores any occurrence of the
EACCES error on the setpgid() call. 

### Kiedy powłoka ustala grupę pierwszoplanową przy pomocy ioctl(2) (realizuje tcsetpgrp(3))?
kiedy wszystkie rury są już utworzone, a procesy potomne są już w nich umieszczone
```
38982 ioctl(10, TIOCSPGRP, [38982])     = 0
```

TIOCSPGRP
const pid_t *argp
Equivalent to tcsetpgrp(fd, *argp).
Set the foreground process group ID of this terminal.

### Na jakiej podstawie powłoka wyznacza kod wyjścia potoku?
na podstawie kodu wyjścia ostatniego procesu w potoku