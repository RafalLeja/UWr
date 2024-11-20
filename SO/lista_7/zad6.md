### Wiemy, że jądro używa stronicowania na żądanie (ang. demand paging) dla wszystkich odwzorowań. Rozważmy program, który utworzył prywatne odwzorowanie pliku w pamięć. Czy mamy gwarancję, że program nie zobaczy modyfikacji zawartości pliku, które zostaną wprowadzone po utworzeniu tego odwzorowania?
#### nie np.:
- program A mapuje plik P do pamięci jako prywatny:
- jądro nic nie robi bo mam demad paging
- program B zmienia plik P
- program A czyta plik P
- jądro dopiero teraz kopiuje plik P do pamięci
- program A czyta zmieniony plik P


### Próba otworzenia open(2) pliku wykonywalnego do zapisu, kiedy ten plik jest załadowany i wykonywany w jakimś procesie, zawiedzie z błędem «ETXTBSY». Podobnie, nie możemy załadować do przestrzeni adresowej execve(2) pliku, który jest otwarty do zapisu. Co złego mogłoby się stać, gdyby system operacyjny pozwolił modyfikować plik wykonywalny, który jest uruchomiony?
- byłby wrażliwy na ataki Arbitrary Code Execution 