### Wyświetl konfigurację terminala przy pomocy polecenia «stty -a». Wskaż znaki, które sterownik terminala: zamienia na sygnały związane z zarządzaniem zadaniami, służą do edycji wiersza. 

```bash
stty -a

speed 38400 baud; rows 19; columns 80; line = 0;
intr = ^C; quit = ^\; erase = ^?; kill = ^U; eof = ^D; eol = <undef>;
eol2 = <undef>; swtch = <undef>; start = ^Q; stop = ^S; susp = ^Z; rprnt = ^R;
werase = ^W; lnext = ^V; discard = ^O; min = 1; time = 0;
-parenb -parodd -cmspar cs8 -hupcl -cstopb cread -clocal -crtscts
-ignbrk -brkint -ignpar -parmrk -inpck -istrip -inlcr -igncr icrnl ixon -ixoff
-iuclc -ixany -imaxbel iutf8
opost -olcuc -ocrnl onlcr -onocr -onlret -ofill -ofdel nl0 cr0 tab0 bs0 vt0 ff0
isig icanon iexten echo echoe echok -echonl -noflsh -xcase -tostop -echoprt
echoctl echoke -flusho -extproc
```
 - zarządzanie: 
   - intr - SIGINT
   - kill - SIGKILL
   - susp - SIGSTP
 - edycja wiersza:
   - werase
   - lnext
   - rprint

### Program może zostać poinformowany o zmianie rozmiaru okna terminala. W tym celu musi zainstalować procedurę obsługi sygnału – którego? 

```bash

gnome-terminal
sudo strace -p <ten drugi gnome>

pselect6(1, [0], NULL, NULL, NULL, {sigmask=[], sigsetsize=8}) = ? ERESTARTNOHAND (To be restarted if no handler)
--- SIGWINCH {si_signo=SIGWINCH, si_code=SI_KERNEL} ---
rt_sigreturn({mask=[]})                 = -1 EINTR (Interrupted system call)
ioctl(0, TIOCGWINSZ, {ws_row=23, ws_col=80, ws_xpixel=0, ws_ypixel=0}) = 0
write(2, "\r\33[K\33[37m\342\225\260\342\224\200\33[0m\33[38;2;255;25"..., 178) = 178
pselect6(1, [0], NULL, NULL, NULL, {sigmask=[], sigsetsize=8}) = ? ERESTARTNOHAND (To be restarted if no handler)
--- SIGWINCH {si_signo=SIGWINCH, si_code=SI_KERNEL} ---
rt_sigreturn({mask=[]})                 = -1 EINTR (Interrupted system call)
ioctl(0, TIOCGWINSZ, {ws_row=22, ws_col=80, ws_xpixel=0, ws_ypixel=0}) = 0
write(2, "\r\33[K\33[37m\342\225\260\342\224\200\33[0m\33[38;2;255;25"..., 178) = 178
```
SIGWINCH


### Jaką procedurą można wczytać nowy rozmiar okna?
```bash

stty columns 40

stty columns 80
```