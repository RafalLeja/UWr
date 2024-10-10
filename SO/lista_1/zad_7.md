- Kopiowanie przez referencje: kopiowanie wzkaźnika zamiast zawartości

###  Czy zamknięcie pliku close(2) w procesie głównym zamyka plik także w dziecku? 
Nie
```
./fileref close
0> dziecko zamyka plik 3
31726> status dziecka = 0
31726> czytanie z pliku 3: Write programs that do one thing and do it well.
```

### Czy odczyt z pliku read(2) zmienia pozycję kursora lseek(2) w drugim procesie?
tak
```
./fileref read
32434> pozycja rodzica po przeczytaniu 8
0> pozycja dziecka po przeczytaniu 16
```

dziecko kopiuje zawartość dopiero jak chce jej użyć