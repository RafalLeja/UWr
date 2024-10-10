### Znajdź pid procesu X-serwera, a następnie używając polecenia «pmap» wyświetl zawartość jego przestrzeni adresowej.

```
ps -e | grep X
pmap -x

3153:   /usr/bin/Xwayland :0 -rootless -noreset -accessx -core -auth /run/user/1000/.mutter-Xwaylandauth.G708U2 -listen 4 -listen 5 -displayfd 6 -initfd 7
000062d241f21000    152K r---- Xwayland
000062d241f47000   1588K r-x-- Xwayland
000062d2420d4000    372K r---- Xwayland
000062d242132000     28K r---- Xwayland
000062d242139000     28K rw--- Xwayland
000062d242140000    240K rw---   [ anon ]
000062d2435b4000  33648K rw---   [ anon ]
00007b4fd5e00000    600K r---- iris_dri.so
00007b4fd5e96000  19456K r-x-- iris_dri.so
00007b4fd7196000  11184K r---- iris_dri.so
00007b4fd7c82000    540K r---- iris_dri.so
00007b4fd7d09000     72K rw--- iris_dri.so
00007b4fd7d1b000   1792K rw---   [ anon ]
00007b4fd8000000    132K rw---   [ anon ]
00007b4fd8021000  65404K -----   [ anon ]
00007b4fdc200000   2048K rw-s-   [ anon ]
00007b4fe1c23000    408K r---- libicuuc.so.70.1
00007b4fe1c89000    972K r-x-- libicuuc.so.70.1
00007b4fe1d7c000    560K r---- libicuuc.so.70.1
00007b4fec0f3000      4K r---- libxshmfence.so.1.0.0
00007b4fec0f4000      4K rw--- libxshmfence.so.1.0.0
00007b4fec0f5000     56K r---- libm.so.6
00007b4fec103000    496K r-x-- libm.so.6
00007b4fec17f000    364K r---- libm.so.6
00007b4fec1da000      4K r---- libm.so.6
00007b4fec1db000      4K rw--- libm.so.6
00007b4fec357000      4K rw--- libXdmcp.so.6.0.0
00007b4fec358000     16K r---- libXfont2.so.2.0.0
00007b4fec35c000    124K r-x-- libXfont2.so.2.0.0
00007b4fec37b000     32K r---- libXfont2.so.2.0.0
00007b4fec383000      4K r---- libXfont2.so.2.0.0
00007b4fec384000      4K rw--- libXfont2.so.2.0.0
00007b4fec385000      4K rw---   [ anon ]

 total           965808K
```

### Zidentyfikuj w niej poszczególne zasoby pamięciowe – tj. stos, stertę, segmenty programu, pamięć anonimową, pliki odwzorowane w pamięć. Należy wyjaśnić znaczenie kolumn wydruku!

| Adres | Kbytes | RSS | Dirty | Mode | Mapping |
|-------|--------|-----|-------|------|---------| 
| Adres | Rozmiar | Rozmiar w RAM | Strony zmodyfikowane ale nie zapisane | Typ dosępu | Nazwa pliku lub urządzenia |



- stos: `pmap -x 3153 | grep stack`
- sterta: `pmap -X 3153 | grep heap`
        Address Perm    Offset Device   Inode   Size    Rss   Pss Pss_Dirty Referenced Anonymous KSM LazyFree ShmemPmdMapped FilePmdMapped Shared_Hugetlb Private_Hugetlb Swap SwapPss Locked THPeligible Mapping
- segmenty programu: spójne bloki pamięci o konkretnym zastosowaniu np. .text, .data. 
    `pmap -x 3153 | grep r-x` - .text
    `pmap -x 3153 | grep r--` - .rodata
    `pmap -x 3153 | grep rw-` - .data
- pamięć anonimowa: pamięć która nie jest odwzorowana w żadnym pliku ani urządzeniu, `pmap -x 3153 | grep anon`
- pliki odwzorowane w pamięci: segment pamięci który ma dokładne odwzorowanie pliku lub zasobu. Może być adresowany bezpośrednio co oszczędza wykonywanie operacji read()/write(). Wszystkie modyfikacje są później zapisywane na dysku. `pmap -x 3153 | grep -E "rw.+.so"`

