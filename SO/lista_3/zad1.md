### Zaprezentuj sytuację, w której proces zostanie osierocony. Uruchom powłokę w nowej instancji emulatora terminala przy pomocy polecenia «xterm -e ’bash -i’». W nowej powłoce wystartuj «sleep 1000» jako zadanie drugoplanowe i sprawdź, kto jest jego rodzicem. 

```bash
gnome-terminal -e 'bash -i'

sleep 1000 &
ps -o pid,ppid,cmd

PID    PPID CMD
5056    2408 bash -i
5263    5056 sleep 1000
5504    5056 ps -o pid,ppid,cmd
```

### Poleceniem «kill» wyślij sygnał «SIGKILL» do uruchomionej wcześniej powłoki i sprawdź, kto stał się nowym rodzicem procesu «sleep». 

```bash 
kill -9 

ps -e -o pid,ppid,cmd | grep sleep

5263    1528 sleep 1000

ps -e -o pid,ppid,cmd | grep 1528

1528       1 /lib/systemd/systemd --user
```

### Zauważ, że powłoka jest liderem sesji. Co się dzieje z sesją, która utraci terminal sterujący? Przeprowadź eksperyment wysyłając «SIGKILL» do emulatora terminala zamiast do powłoki.

```bash

sudo strace -e trace=signal -p <powłoka>
kill -9 <powłoka>

strace: Process 7248 attached
+++ killed by SIGKILL +++

sudo strace -e trace=signal -p <powłoka>
ps -e | grep gnome-terminal
kill -9 <emulator>
--- SIGHUP {si_signo=SIGHUP, si_code=SI_USER, si_pid=8125, si_uid=1000} ---
rt_sigreturn({mask=[]})                 = -1 EINTR (Interrupted system call)
--- SIGHUP {si_signo=SIGHUP, si_code=SI_KERNEL} ---
--- SIGCONT {si_signo=SIGCONT, si_code=SI_KERNEL} ---
rt_sigreturn({mask=[]})                 = -1 EINTR (Interrupted system call)
rt_sigprocmask(SIG_BLOCK, NULL, [], 8)  = 0
rt_sigaction(SIGINT, {sa_handler=0x59e2cf285150, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7d7173842520}, {sa_handler=0x59e2cf2e6a20, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7d7173842520}, 8) = 0
rt_sigaction(SIGHUP, {sa_handler=0x59e2cf285530, sa_mask=[HUP INT ILL TRAP ABRT BUS FPE USR1 SEGV USR2 PIPE ALRM TERM XCPU XFSZ VTALRM SYS], sa_flags=SA_RESTORER, sa_restorer=0x7d7173842520}, {sa_handler=0x59e2cf2e6a20, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7d7173842520}, 8) = 0
rt_sigaction(SIGALRM, {sa_handler=0x59e2cf285530, sa_mask=[HUP INT ILL TRAP ABRT BUS FPE USR1 SEGV USR2 PIPE ALRM TERM XCPU XFSZ VTALRM SYS], sa_flags=SA_RESTORER, sa_restorer=0x7d7173842520}, {sa_handler=0x59e2cf2e6a20, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7d7173842520}, 8) = 0
rt_sigaction(SIGWINCH, {sa_handler=0x59e2cf283300, sa_mask=[], sa_flags=SA_RESTORER|SA_RESTART, sa_restorer=0x7d7173842520}, {sa_handler=0x59e2cf2e6a30, sa_mask=[], sa_flags=SA_RESTORER|SA_RESTART, sa_restorer=0x7d7173842520}, 8) = 0
kill(12059, SIGHUP)                     = 0
--- SIGHUP {si_signo=SIGHUP, si_code=SI_USER, si_pid=12059, si_uid=1000} ---
rt_sigreturn({mask=[]})                 = 0
rt_sigprocmask(SIG_BLOCK, [HUP INT QUIT ALRM TERM TSTP TTIN TTOU], [], 8) = 0
rt_sigaction(SIGINT, {sa_handler=0x59e2cf2e6a20, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7d7173842520}, {sa_handler=0x59e2cf285150, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7d7173842520}, 8) = 0
rt_sigaction(SIGTERM, {sa_handler=0x59e2cf2e6a20, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7d7173842520}, {sa_handler=SIG_IGN, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7d7173842520}, 8) = 0
rt_sigaction(SIGTERM, {sa_handler=SIG_IGN, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7d7173842520}, {sa_handler=0x59e2cf2e6a20, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7d7173842520}, 8) = 0
rt_sigaction(SIGHUP, {sa_handler=0x59e2cf2e6a20, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7d7173842520}, {sa_handler=0x59e2cf285530, sa_mask=[HUP INT ILL TRAP ABRT BUS FPE USR1 SEGV USR2 PIPE ALRM TERM XCPU XFSZ VTALRM SYS], sa_flags=SA_RESTORER, sa_restorer=0x7d7173842520}, 8) = 0
rt_sigaction(SIGQUIT, {sa_handler=0x59e2cf2e6a20, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7d7173842520}, {sa_handler=SIG_IGN, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7d7173842520}, 8) = 0
rt_sigaction(SIGQUIT, {sa_handler=SIG_IGN, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7d7173842520}, {sa_handler=0x59e2cf2e6a20, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7d7173842520}, 8) = 0
rt_sigaction(SIGALRM, {sa_handler=0x59e2cf2e6a20, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7d7173842520}, {sa_handler=0x59e2cf285530, sa_mask=[HUP INT ILL TRAP ABRT BUS FPE USR1 SEGV USR2 PIPE ALRM TERM XCPU XFSZ VTALRM SYS], sa_flags=SA_RESTORER, sa_restorer=0x7d7173842520}, 8) = 0
rt_sigaction(SIGTSTP, {sa_handler=0x59e2cf2e6a20, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7d7173842520}, {sa_handler=SIG_IGN, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7d7173842520}, 8) = 0
rt_sigaction(SIGTSTP, {sa_handler=SIG_IGN, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7d7173842520}, {sa_handler=0x59e2cf2e6a20, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7d7173842520}, 8) = 0
rt_sigaction(SIGTTOU, {sa_handler=0x59e2cf2e6a20, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7d7173842520}, {sa_handler=SIG_IGN, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7d7173842520}, 8) = 0
rt_sigaction(SIGTTOU, {sa_handler=SIG_IGN, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7d7173842520}, {sa_handler=0x59e2cf2e6a20, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7d7173842520}, 8) = 0
rt_sigaction(SIGTTIN, {sa_handler=0x59e2cf2e6a20, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7d7173842520}, {sa_handler=SIG_IGN, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7d7173842520}, 8) = 0
rt_sigaction(SIGTTIN, {sa_handler=SIG_IGN, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7d7173842520}, {sa_handler=0x59e2cf2e6a20, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7d7173842520}, 8) = 0
rt_sigprocmask(SIG_SETMASK, [], NULL, 8) = 0
rt_sigaction(SIGWINCH, {sa_handler=0x59e2cf2e6a30, sa_mask=[], sa_flags=SA_RESTORER|SA_RESTART, sa_restorer=0x7d7173842520}, {sa_handler=0x59e2cf283300, sa_mask=[], sa_flags=SA_RESTORER|SA_RESTART, sa_restorer=0x7d7173842520}, 8) = 0
rt_sigaction(SIGINT, {sa_handler=0x59e2cf285150, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7d7173842520}, {sa_handler=0x59e2cf2e6a20, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7d7173842520}, 8) = 0
rt_sigaction(SIGHUP, {sa_handler=0x59e2cf285530, sa_mask=[HUP INT ILL TRAP ABRT BUS FPE USR1 SEGV USR2 PIPE ALRM TERM XCPU XFSZ VTALRM SYS], sa_flags=SA_RESTORER, sa_restorer=0x7d7173842520}, {sa_handler=0x59e2cf2e6a20, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7d7173842520}, 8) = 0
rt_sigaction(SIGALRM, {sa_handler=0x59e2cf285530, sa_mask=[HUP INT ILL TRAP ABRT BUS FPE USR1 SEGV USR2 PIPE ALRM TERM XCPU XFSZ VTALRM SYS], sa_flags=SA_RESTORER, sa_restorer=0x7d7173842520}, {sa_handler=0x59e2cf2e6a20, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7d7173842520}, 8) = 0
rt_sigaction(SIGWINCH, {sa_handler=0x59e2cf283300, sa_mask=[], sa_flags=SA_RESTORER|SA_RESTART, sa_restorer=0x7d7173842520}, {sa_handler=0x59e2cf2e6a30, sa_mask=[], sa_flags=SA_RESTORER|SA_RESTART, sa_restorer=0x7d7173842520}, 8) = 0
rt_sigprocmask(SIG_BLOCK, [CHLD], [], 8) = 0
rt_sigprocmask(SIG_SETMASK, [], NULL, 8) = 0
rt_sigprocmask(SIG_SETMASK, [], NULL, 8) = 0
rt_sigaction(SIGHUP, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7d7173842520}, {sa_handler=0x59e2cf285530, sa_mask=[HUP INT ILL TRAP ABRT BUS FPE USR1 SEGV USR2 PIPE ALRM TERM XCPU XFSZ VTALRM SYS], sa_flags=SA_RESTORER, sa_restorer=0x7d7173842520}, 8) = 0
kill(12059, SIGHUP)                     = 0
--- SIGHUP {si_signo=SIGHUP, si_code=SI_USER, si_pid=12059, si_uid=1000} ---
+++ killed by SIGHUP +++

```