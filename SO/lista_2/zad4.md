### Uruchom program «xeyes» po czym użyj na nim polecenia «kill», «pkill» i «xkill». Który sygnał jest wysyłany domyślnie?

```bash
xeyes &

kill - domyślnie TERM
pkill - domyślnie TERM
xkill - odłącza od Xserver?
```

### Przy pomocy kombinacji klawiszy «CTRL+Z» wyślij «xeyes» sygnał «SIGTSTP», a następnie wznów jego wykonanie.

```bash
xeyes 
CTRL+Z
fg
```

### Przeprowadź inspekcję pliku «/proc/pid/status» i wyświetl maskę sygnałów oczekujących na dostarczenie. Pokaż jak będzie się zmieniać, gdy będziemy wysyłać wstrzymanemu procesowi kolejno: «SIGUSR1», «SIGUSR2», «SIGHUP» i «SIGINT».

[man proc_pid_status](https://man7.org/linux/man-pages/man5/proc_pid_status.5.html)

- SigQ - kolejka sygnałów
- SigPnd, ShdPnd:

  Mask (expressed in hexadecimal) of signals pending for thread and for process as a whole (see
  pthreads(7) and signal(7)).
- SigBlk, SigIgn, SigCgt

  Masks (expressed in hexadecimal) indicating signals being blocked, ignored, and caught (see signal(7)).

```bash
xeyes &
cat /proc/$(pidof xeyes)/status

>ShgPnd: 0000000000000000

xeyes
CTRL+Z
kill -s SIGUSR1 $(pidof xeyes)
cat /proc/$(pidof xeyes)/status

>ShdPnd: 0000000000000200

xeyes
CTRL+Z
kill -s SIGUSR2 $(pidof xeyes)
cat /proc/$(pidof xeyes)/status

>ShdPnd: 0000000000000800

xeyes
CTRL+Z
kill -s SIGHUP $(pidof xeyes)
cat /proc/$(pidof xeyes)/status

>ShdPnd: 0000000000000001

xeyes
CTRL+Z
kill -s SIGINT $(pidof xeyes)
cat /proc/$(pidof xeyes)/status

>ShdPnd: 0000000000000002
```

### Co opisują pozostałe pola pliku «status» dotyczące sygnałów? Który sygnał zostanie dostarczony jako pierwszy po wybudzeniu procesu?

```
xeyes
CTRL+Z
kill -s SIGUSR1 $(pidof xeyes)
kill -s SIGUSR2 $(pidof xeyes)
kill -s SIGHUP $(pidof xeyes)
kill -s SIGINT $(pidof xeyes)
fg

>Hangup
```
