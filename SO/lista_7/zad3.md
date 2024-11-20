### Przy pomocy polecenia «cat /proc/$(pgrep Xorg)/status | egrep ’Vm|Rss’» wyświetl zużycie pamięci procesu wykonującego kod X-serwera. Na podstawie podręcznika proc(5) wyjaśnij znaczenie poszczególnych pól.
```bash
cat /proc/$(pgrep Xway)/status | egrep 'Vm|Rss'

VmPeak:	 1111028 kB     // peak virtual memory size    
VmSize:	  994348 kB     // virtual memory size
VmLck:	       0 kB     // locked memory size (see mlock(2)).
VmPin:	       0 kB     // pinned memory size hese are pages that can't be moved because something needs to  directly access physical memory.
VmHWM:	  153048 kB     // peak resident set size ("high water mark")
VmRSS:	   47140 kB     // resident set size
RssAnon:	   22872 kB // size of resident anonymous memory
RssFile:	    8256 kB // size of resident file mappings
/RssShmem:	   16012 kB // size of resident shared memory
VmData:	  118204 kB     // size of data
VmStk:	     132 kB     // size of stack
VmExe:	    1588 kB     // size of text
VmLib:	  137812 kB     // size of shared library code
VmPTE:	     672 kB     // size of page table entries
VmSwap:	   25684 kB     // size of swap
```

### Przypomnij jaka jest różnica między zbiorem roboczym i rezydentnym procesu.
- roboczy: to zbiór wszystkich stron, które proces może w danym momencie używać
- rezydentny: to zbiór stron, które są fizycznie obecne w pamięci RAM

### Napisz krótki skrypt (np. w języku Python lub awk(1)), który wyznaczy sumę «VmSize» i osobno sumę «VmRSS» wszystkich procesów. Czemu ta druga wartość nie pokrywa się z rozmiarem używanej pamięci raportowanym przez polecenie «vmstat -s»?

skrypt liczący sumę VmSize i VmRSS wszystkich procesów, skoro dwa procesy mogą współdzielić tą samą stronę pamięci, to liczymy je podwójnie

vmstat -s liczy poprawnie, bo uwzględnia współdzielenie stron pamięci między procesami

```bash
awk '/VmSize|VmRSS/ {if ($1 ~ /VmSize/) vmsize += $2; if ($1 ~ /VmRSS/) vmrss += $2} END {print "Total VmSize: " vmsize " kB\nTotal VmRSS: " vmrss " kB"}' /proc/*/status 2>/dev/null

vmstat -s
```