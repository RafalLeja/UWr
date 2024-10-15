### Na podstawie dokumentacji fork(2) (§8.3) i execve(2) (§8.10) wymień najważniejsze zasoby procesu, które są (a) dziedziczone przez proces potomny (b) przekazywane do nowego programu załadowanego do przestrzeni adresowej.

- fork: Besides the open files, numerous other properties of the parent are inherited by the
    child:
    - Real user ID, real group ID, effective user ID, and effective group ID
    - Supplementary group IDs
    - Process group ID
    - Session ID
    - Controlling terminal
    - The set-user-ID and set-group-ID flags
    - Current working directory
    - Root directory
    - File mode creation mask
    - Signal mask and dispositions
    - The close-on-exec flag for any open file descriptors
    - Environment
    - Attached shared memory segments
    - Memory mappings
    - Resource limits
- exec
    We've mentioned that the process ID does not change after an exec, but the new
program inherits additional properties from the calling process:
    - Process ID and parent process ID
    - Real user ID and real group ID
    - Supplementary group IDs
    - Process group ID
    - Session ID
    - Controlling terminal
    - Time left until alarm clock
    - Current working directory
    - Root directory
    - File mode creation mask
    - File locks
    - Process signal mask
    - Pending signals
    - Resource limits
    - Nice value (on XSI-conformant systems; see Section 8.16)
    - Values for tms_utime, tms_stime, tms_cutime, and tms_cstime

### Czemu przed wywołaniem fork należy opróżnić bufory biblioteki stdio(3)?

```
The standard I/O library, however, is buffered. Recall from Section 5.12 that standard output is line buffered if it’s connected to a terminal device; otherwise, it’s fully buffered. When we run the program interactively, we get only a single copy of the first printf line, because the standard output buffer is flushed by the newline. When we redirect standard output to a file, however, we get two copies of the printf line. In this second case, the printf before the fork is called once, but the line remains in the buffer when fork is called. This buffer is then copied into the child when the parent’s data space is copied to the child. Both the parent and the child now have a standard I/O buffer with this line in it. The second printf, right before the exit, just appends its data to the existing buffer. When each process terminates, its copy of the buffer is finally flushed.
```

Bufor zostanie skopiowany do dziecka i wypiszemy dwa razy to samo.

### Co jądro robi w trakcie wywołania execve z konfiguracją zainstalowanych procedur obsługi sygnałów?

[signals and exec](https://www.cs.uleth.ca/~holzmann/C/system/signals.html)

exec usuwa wszystkie zainstalowane procedury obsługi sygnałów i ustawia je na SIG_DFL, a te z SIG_IGN na SIG_IGN.