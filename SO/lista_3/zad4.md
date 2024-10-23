### Urządzenie terminala zajmuje się interpretacją znaków i sekwencji sterujących2 przychodzących od sterownika terminala, oraz przetwarzaniem zdarzeń od użytkownika, które zostają zamienione na znaki lub sekwencje znaków, a następnie wysłane do sterownika terminala. Posługując się poleceniem «echo -e ’sterujacy’; read» zaprezentuj działanie znaków sterujących oraz sekwencji «CSI». 

```bash

echo -e 'sterujacy'; read

^R # Reprint
^W # erase

echo -e "\033[31mTo jest czerwony tekst\033[0m"

```

### Uruchom polecenie «cat» i sprawdź jak zachowuje się naciśnięcie klawiszy funkcyjnych i kursora. Czemu w tym przypadku zachowanie programu «cat» jest inne niż powłoki poleceń?

```bash

cat
```

klawisze są wysyłane bezpośrednio do <cat>, są wykonywane dopiero jak cat je odeśle