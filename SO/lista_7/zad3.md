### Przy pomocy polecenia «cat /proc/$(pgrep Xorg)/status | egrep ’Vm|Rss’» wyświetl zużycie pamięci procesu wykonującego kod X-serwera. Na podstawie podręcznika proc(5) wyjaśnij znaczenie
poszczególnych pól. Przypomnij jaka jest różnica między zbiorem roboczym i rezydentnym procesu. Napisz
krótki skrypt (np. w języku Python lub awk(1)), który wyznaczy sumę «VmSize» i osobno sumę «VmRSS»
wszystkich procesów. Czemu ta druga wartość nie pokrywa się z rozmiarem używanej pamięci raportowanym
przez polecenie «vmstat -s»?