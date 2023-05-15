### Przepełnienie bufora
Polega na zapisaniu większej ilości danych do pamięci niż ilość zarezerwowanego na ten cel miejsca. Prowadzi to do nadpisania danych znajdujących się bezpośrednio za wyznaczonym miejscem. 

### Programowanie zorientowane na powroty 
Technika wykorzystująca lukę w zabezpieczeniach komputera , która umożliwia atakującemu wykonanie kodu w obecności zabezpieczeń, takich jak ochrona przestrzeni wykonywalnej i podpisywanie kodu . W tej technice atakujący przejmuje kontrolę nad stosem wywołań w celu przejęcia przepływu sterowania programem, a następnie wykonuje starannie wybrane sekwencje instrukcji maszynowych , które są już obecne w pamięci maszyny, zwane „gadżetami”. Każdy gadżet zwykle kończy się instrukcją powrotu i znajduje się w podprogramie w ramach istniejącego programu i / lub kodu biblioteki współdzielonej. Połączone ze sobą gadżety umożliwiają atakującemu wykonywanie dowolnych operacji na maszynie wykorzystującej mechanizmy obronne, które udaremniają prostsze ataki.

### Wyszukiwanie adresów:
``` 
objdump -d ropex | grep "gadget":  
0000000000401d7b <gadget>:
little endian - 7b1d 4000
```
``` 
objdump -d ropex | grep "syscall":
47a88d:       0f 05                   syscall
little endian - 8da8 4700
```

### Tłumaczenie:
`xxd -r ropex.in.txt >ropex.in`

