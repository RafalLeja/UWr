### Słownik:

* rodzic-dziecko: hierarchia w której rodzic to program który uruchamia podproces - dziecko
* identyfikator procesu: unikatowa liczba przypisana do każdego procesu
* identyfikator grupy procesów: id leadera grupy procesów, grupy służą do przekazywania sygnałów
* idyntyfikator rodzica: id rodzica który stworzył proces
* właściciel: użytkownik, grupa użytkowników do którego należy proces. Od tego zależą uprawnienia dostępu dla procesu.
* wątki jądra: wątek który działa w przestrzeni adresowej jądra, wątki jądra mają wspólne zmienne globalne więc wymagają wspólnej synchronizacji
* hierarchia procesów: 

### Na wydruku zidentyfikuj identyfikator procesu, identyfikator grupy procesów, identyfikator rodzica oraz właściciela procesu. Kto jest rodzicem procesu init? Wskaż, które z wyświetlonych zadań są wątkami jądra.

```
ps -eo user,pid,ppid,pgid,tid,pri,stat,wchan,cmd
```
```
pri         PRI       priority

tgid        TGID      a number representing the thread group to which a task belongs (alias pid).  It is the process ID of the thread group leader.

wchan       WCHAN     name of the kernel function in which the process is sleeping, a "-" if the process is running, or a "*" if the process is
                             multi-threaded and ps is not displaying threads.



USER         PID    PPID    PGID     TID PRI STAT WCHAN  CMD
root           1       0       1       1  19 Ss   -      /sbin/init splash
root           2       0       0       2  19 S    -      [kthreadd]
root           3       2       0       3  19 S    -      [pool_workqueue_release]
root           4       2       0       4  39 I<   -      [kworker/R-rcu_g]
root           5       2       0       5  39 I<   -      [kworker/R-rcu_p]
root           6       2       0       6  39 I<   -      [kworker/R-slub_]
root           7       2       0       7  39 I<   -      [kworker/R-netns]
...
rafal       1581    1462    1581    1581  19 Ssl+ do_pol /usr/libexec/gdm-wayland-session env GNOME_SHELL_SESSION_MODE=ubuntu /usr/bin/gnome-session --session=ubuntu
rafal       1584    1581    1581    1584  19 Sl+  do_pol /usr/libexec/gnome-session-binary --session=ubuntu
rafal       1654    1474    1654    1654  19 Ssl  do_pol /usr/libexec/gnome-session-ctl --monitor
rafal       1664    1474    1664    1664  19 Ssl  do_pol /usr/libexec/gvfsd
rafal       1672    1474    1664    1672  19 Sl   futex_ /usr/libexec/gvfsd-fuse /run/user/1000/gvfs -f
rafal       1674    1474    1674    1674  19 Ssl  do_pol /usr/libexec/gnome-session-binary --systemd-service --session=ubuntu
rafal       1696    1674    1674    1696  19 Sl   do_pol /usr/libexec/at-spi-bus-launcher --launch-immediately
```

### Jakie jest znaczenie poszczególnych znaków w kolumnie STAT?
```
PROCESS STATE CODES
       Here are the different values that the s, stat and state output specifiers (header "STAT" or "S") will display to describe the state of a process:

               D    uninterruptible sleep (usually IO)
               I    Idle kernel thread
               R    running or runnable (on run queue)
               S    interruptible sleep (waiting for an event to complete)
               T    stopped by job control signal
               t    stopped by debugger during the tracing
               W    paging (not valid since the 2.6.xx kernel)
               X    dead (should never be seen)
               Z    defunct ("zombie") process, terminated but not reaped by its parent

       For BSD formats and when the stat keyword is used, additional characters may be displayed:

               <    high-priority (not nice to other users)
               N    low-priority (nice to other users)
               L    has pages locked into memory (for real-time and custom IO)
               s    is a session leader
               l    is multi-threaded (using CLONE_THREAD, like NPTL pthreads do)
               +    is in the foreground process group
```

### Wyświetl drzewiastą reprezentację hierarchii procesów poleceniem `pstree` – które z zadań są wątkami?
```
pstree

systemd─┬─ModemManager───2*[{ModemManager}]
        ├─NetworkManager───2*[{NetworkManager}]
        ├─accounts-daemon───2*[{accounts-daemon}]
        ├─acpid
        ├─avahi-daemon───avahi-daemon
        ├─bluetoothd
        ├─boltd───2*[{boltd}]
        ├─colord───2*[{colord}]
        ├─cron
```

wątki to te z wąsami
