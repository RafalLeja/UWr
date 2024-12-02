## B¦dziemy rozwa»a¢ zadanie Next Sentence Prediction (czyli zadanie, w którym na wej±ciu mamy dwa zdania i nale»y okre±li¢, czy s¡ one kolejnymi zdaniami tekstu (czyli czy drugie zdanie jest w tek±cie bezpo±rednio po pierwszym). Zadanie to wyst¦puje w dwóch wariantach:
## a) Przykªady negatywne s¡ losowane z caªego korpusu.
liczenie prawdopodobieństwa a|b vs b|a lub,
do pierwszego zdania generujemy jedno lub dwa zdania, po czym doklejamy drugie i liczmy prawdopodobieństwo.

## b) Przykªady negatywne s¡ kolejnymi zdaniami, w których zmienili±my kolejno±¢.
liczenie prawdopodobieństwa a|b vs b|a
za pomocą word2vec-a, sprawdzamy odległość między pierwszymi wyrazami drugiego zdania, a ostatnimi wyrazami pierwszego zdania i na odwrót.

## Oczywi±cie przykªady pozytywne, to po prostu pary kolejnych zda« z tekstu. Zaproponuj rozwi¡zanie obu tych wariantów, wykorzystuj¡ce model taki jak Papuga. Dodatkowo dla wybranego wariantu zaproponuj rozwi¡zanie niekorzystaj¡ce z zaawansowanych sieci neuronowych (jak chcesz, mo»esz skorzysta¢ z word2vec-a, lub podobnych modeli, ale nie jest to wymagane).