### W każdym z poniższych przypadków zakładamy, że początkowa tożsamość naszego procesu to: ruid=1000, euid=0, suid=0. Jak zmieni się tożsamość procesu po wywołaniu następujących funkcji: 
### (a) setuid(2000), 
### (b) setreuid(-1, 2000), 
### (c) seteuid(2000), 
### (d) setresuid(-1, 2000, 3000). Odpowiedź uzasadnij posługując się podręcznikami systemowymi setuid(2), setreuid(2), setresuid(2).

- a) setuid(2000) - ustawia ruid na 2000, euid na 2000, suid na 2000
- b) setreuid(-1, 2000) - nie zmienia ruid, euid na 2000, suid nie zmienia się
- c) seteuid(2000) - nie zmienia ruid, euid na 2000, suid nie zmienia się
- d) setresuid(-1, 2000, 3000) - nie zmienia ruid, euid na 2000, suid na 3000


### Czy proces z tożsamością ruid=0, euid=1000, suid=1000 jest uprzywilejowany? Odpowiedź uzasadnij.
Nie, proces nie jest uprzywilejowany, ponieważ euid nie jest równy 0.