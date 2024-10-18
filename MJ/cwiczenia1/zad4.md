### Na Olimpiadzie Sztucznej Inteligencji byªo zadanie Riddles2. W skrócie, chodziªo o przypisanie sªów tekstom opisuj¡cym te sªowa, przy czym odpowiedzi nale»aªy do znanego zbioru (zawieraj¡cego okoªo 10K sªów). Przykªadowym tekstem byªo: kobieta podró»uj¡ca ±rodkiem transportu, np. samolotem, poci¡giem, statkiem dla którego odpowiedzi¡ jest pasa»erka3.
    Uczestnicy Olimpiady rozwi¡zuj¡cy mieli do dyspozycji denicje sªów z Wiktionary, ale my
    zaªo»ymy, »e mamy dost¦p jedynie do modelu j¦zykowego. Odpowiedz na pytania:
    a) Czy da sie zmusi¢ który± z naszych modeli do tego, »eby rozwi¡zywaª to zadanie w trybie generacji. Jaka strategia wydaje Ci si¦ obiecuj¡ca?
    b) Czy funkcja oceniania prawdopodobie«stwa zdania mo»e by¢ z sukcesem u»yta w tym zadaniu?
    (jaki jest gªówny problem z jej u»yciem)

### a)
    Jeśli możemy, należy przetrenować model na zbiorze danych zawierających definicje słów. Wtedy model będzie mógł generować definicje słów na podstawie ich opisu.

    Następnie na z wektoru końcowego prawdopodobieństwa słów, które model wygenerował, wybieramy najbardziej prawdopodobny token z naszego zbioru słów.

### b)    
    Ponieważ mamy 10K słów, metoda prawdopodobieństwa zdania będzie potrzebowała bardzo dużej ilości obliczeń