## Zaproponuj jaki± sposób do wyznaczania (bezkontekstowych) osadze« w¦zªów w grae (na przykªad osób w sieciach spoªeczno±ciowych, lmów i u»ytkowników Netlixa, ...). Twój sposób powienien korzysta¢ z oryginalnego Word2Vec-a.

Aby użyć Word2Vec musimy najpierw uzyskać korpus.

Korpus możemy złożyć z losowych ścieżek (zdań).

Konstrukcja losowej ścieżki:
1. Wybierz losowy węzeł.
2. Wybierz losowego sąsiada.
3. Przejdź do sąsiada.
3. Powtórz

W ten sposób model nauczy się które węzły są ze sobą powiązane.