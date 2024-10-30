### Uruchom potok (ang. pipeline) «ps -ef | grep sh | wc -l > cnt» w powłoce utworzonej przy pomocy polecenia «strace -o pipeline.log -f dash». 
```bash
strace -o pipeline.log -f dash
ps -ef | grep sh | wc -l > cnt
cat pipeline.log
```
### Na podstawie zawartości pliku «pipeline.log» opisz jak powłoka realizuje funkcje łączenia procesów rurami (ang. pipe) i wykonuje przekierowanie standardowego wyjścia do pliku. W szczególności wskaż które procesy i w jakiej kolejności będą wołały następujące wywołania systemowe: openat(2) z flagą «O_CREAT» (realizuje creat(2)), dup2(2), pipe(2), close(2), clone(2) (realizuje fork(2)) i execve(2). Zwróć szczególną uwagę na to kiedy powłoka tworzy rury i kiedy są zamykane ich poszczególne końce.
```bash
grep -E 'O_CREAT|dup2|pipe|close|clone|execve' pipeline.log
grep -E 'O_CREAT|dup2|pipe|close.[^6] |clone|execve' pipeline.log

8982 execve("/usr/bin/dash", ["dash"], 0x7fffbe04e128 /* 64 vars */) = 0
38982 pipe2([3, 4], 0)          // utwórz rurę 3 -> 4
38982 clone(child_stack=NULL,   // utwórz process ps
38982 close(4 <unfinished ...>
38982 pipe2( <unfinished ...>
38994 close(3 <unfinished ...>
38982 <... pipe2 resumed>[4, 5], 0)     = 0
38982 clone(child_stack=NULL, flags=CLONE_CHILD_CLEARTID|CLONE_CHILD_SETTID|SIGCHLD <unfinished ...>
38994 dup2(4, 1)                        = 1
38994 execve("/usr/bin/ps", ["ps", "-ef"], 0x6506fff052e8 /* 64 vars */ <unfinished ...>
38982 <... clone resumed>, child_tidptr=0x7dcab6f69a10) = 38995
38982 close(5 <unfinished ...>
38994 <... execve resumed>)             = 0
38982 clone(child_stack=NULL, flags=CLONE_CHILD_CLEARTID|CLONE_CHILD_SETTID|SIGCHLD <unfinished ...>
38995 dup2(3, 0 <unfinished ...>
38995 <... dup2 resumed>)               = 0
38995 close(3 <unfinished ...>
38982 <... clone resumed>, child_tidptr=0x7dcab6f69a10) = 38996
38995 dup2(5, 1 <unfinished ...>
38994 close(3 <unfinished ...>
38995 <... dup2 resumed>)               = 1
38995 close(5 <unfinished ...>
38982 close(4 <unfinished ...>
38995 execve("/usr/bin/grep", ["grep", "sh"], 0x6506fff05318 /* 64 vars */ <unfinished ...>
38995 <... execve resumed>)             = 0
38996 dup2(4, 0 <unfinished ...>
38994 close(3 <unfinished ...>
38996 <... dup2 resumed>)               = 0
38996 close(4 <unfinished ...>
38996 openat(AT_FDCWD, "cnt", O_WRONLY|O_CREAT|O_TRUNC, 0666 <unfinished ...>
38996 close(1 <unfinished ...>
38996 dup2(3, 1 <unfinished ...>
38996 <... dup2 resumed>)               = 1
38996 close(3 <unfinished ...>
38996 execve("/usr/bin/wc", ["wc", "-l"], 0x6506fff05368 /* 64 vars */ <unfinished ...>
38996 <... execve resumed>)             = 0

```