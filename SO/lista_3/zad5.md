### Mając na uwadze bieżącą konfigurację sterownika terminala wykonaj następujące polecenia:
### 1. Wstrzymaj zadanie pierwszoplanowe «sleep 1000» i przy pomocy wbudowanego polecenia powłoki «bg» przenieś to zadanie do wykonania w tle. Jaki sygnał został użyty do wstrzymania zadania?

```bash
gnome-terminal
sleep 1000

pgrep sleep
sudo strace -p

^Z
bg

strace: Process 24364 attached
restart_syscall(<... resuming interrupted read ...>) = ? ERESTART_RESTARTBLOCK (Interrupted by signal)
--- SIGTSTP {si_signo=SIGTSTP, si_code=SI_KERNEL} ---
--- stopped by SIGTSTP ---
--- SIGCONT {si_signo=SIGCONT, si_code=SI_USER, si_pid=23688, si_uid=1000} ---
restart_syscall(<... resuming interrupted restart_syscall ...>
```

### 2. Uruchom «find /». W trakcie jego działania naciśnij na przemian kilkukrotnie kombinację klawiszy «CTRL+S» oraz «CTRL+Q». Czemu program zatrzymuje się i wznawia swoją pracę, skoro sterownik terminala nie wysyłał do niego żadnych sygnałów?
```bash
find /
```

program zatrzymuje się, tty driver tylko zatrzymuje wyświetlanie stdout tego procesu

### 3. Uruchom w powłoce «bash» polecenie «cat - &». Czemu zadanie zostało od razu wstrzymane? Jaki sygnał otrzymało? Zakończ to zdanie wbudowanym poleceniem powłoki «kill».
```bash
cat -

ps -e | grep cat
sudo strace -p

^Z
bg
kill
fg

strace: Process 26842 attached
read(0, 0x7d7143401000, 131072)         = ? ERESTARTSYS (To be restarted if SA_RESTART is set)
--- SIGTSTP {si_signo=SIGTSTP, si_code=SI_KERNEL} ---
--- stopped by SIGTSTP ---
--- SIGCONT {si_signo=SIGCONT, si_code=SI_USER, si_pid=23688, si_uid=1000} ---
read(0, 0x7d7143401000, 131072)         = ? ERESTARTSYS (To be restarted if SA_RESTART is set)
--- SIGTTIN {si_signo=SIGTTIN, si_code=SI_KERNEL} ---
--- stopped by SIGTTIN ---
--- SIGTERM {si_signo=SIGTERM, si_code=SI_USER, si_pid=23688, si_uid=1000} ---
+++ killed by SIGTERM +++
```

proces jest wstrzymany ponieważ czeka na wejście z terminala, a skoro terminal nie jest z nim połączony, lepiej jest go zatrzymać aby nie marnować zasobów

### 4. Porównaj działanie polecenia «cat /etc/shells &» przed i po zmianie konfiguracji terminala poleceniem «stty tostop». Jaki efekt ma włączenie flagi «tostop» na zachowanie sterownika terminala?
* [-]tostop
        stop background jobs that try to write to the terminal

```bash

cat /etc/shells &

[1] 27585
# /etc/shells: valid login shells
/bin/sh
/bin/bash
/usr/bin/bash
/bin/rbash
/usr/bin/rbash
/usr/bin/sh
/bin/dash
/usr/bin/dash
[1]+  Done                    cat /etc/shells

stty tostop

cat /etc/shells &

[1] 27650

[1]+  Stopped                 cat /etc/shells
```

### 5. Wykonaj polecenie «stty -echoctl». Wyjaśnij co zmieniło się w konfiguracji terminala i zaprezentuj na przykładzie programu «cat» pokaż jak zmieniło się przetwarzanie znaków sterujących.

* [-]ctlecho
        echo control characters in hat notation ('^c')

```bash

stty -echoclt
cat
```