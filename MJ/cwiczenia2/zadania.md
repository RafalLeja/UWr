## Zadanie 2
### Zastanów si¦, dlaczego miaªoby to dziaªa¢ w ten sposób?
Modele często generują teksty bardziej spójne, płynne i pozbawione nietypowych wyrażeń, przez co ich perplexity może być zazwyczaj niższe (są bardziej „uporządkowane” i spójne niż ludzki język). Stąd pomysł, że teksty z wyższą wartością perplexity mogłyby sugerować bardziej „nienaturalne” pochodzenie.

### Dlaczego to nie jest rozwi¡zanie idealne i jak u»ytkownik takiego modelu jak ChatGPT mo»e kontrolowa¢ perplexity wygenerowanego tekstu
Generowanie tekstów imitujących styl różnych autorów, z uwzględnieniem ich specyficznych cech stylistycznych (np. nieregularności, idiomów) może zmniejszyć rozpoznawalność takiego tekstu jako wygenerowanego przez AI.

## Zadanie 3

W zadaniu polegającym na generowaniu tekstu przy użyciu N-gramów pojawia się wyzwanie, gdy musimy wygenerować tekst, który spełnia określone warunki (np. zawiera dany wyraz w określonym miejscu). Metoda naturalna, czyli generowanie tekstu sekwencyjnie od lewej do prawej i weryfikacja warunku na końcu, jest nieefektywna, ponieważ nie kontroluje powstawania wymaganych wzorców w trakcie procesu generowania. W wyniku tego metoda ta często wymaga wielu powtórzeń generacji, zanim uzyskamy tekst spełniający warunki, co jest kosztowne obliczeniowo i czasochłonne.

Oto propozycje algorytmów dla każdego z przypadków:

### a) Losowanie tekstu o długości \( M \), który na pozycji \( k \) ma określony wyraz

W tej sytuacji zależy nam na tym, aby konkretny wyraz znalazł się na określonej pozycji w ciągu N-gramów. Aby zwiększyć szanse na wygenerowanie tekstu spełniającego ten warunek, możemy:
1. Rozpocząć generację od ustalenia wyrazu na pozycji \( k \).
2. Następnie losować N-gramy tak, aby:
   - Budować tekst od pozycji \( k \) w kierunku początkowym oraz od pozycji \( k \) w kierunku końcowym, tworząc spójny ciąg N-gramów.
3. Dzięki tej metodzie mamy pewność, że na pozycji \( k \) znajdzie się wyraz spełniający wymaganie, a dalsza generacja może być prowadzona zgodnie z regułami N-gramów.

### b) Losowanie tekstu o długości \( M \), który na pozycjach parzystych ma określone wyrazy

Tutaj potrzebujemy kontrolować wyrazy na pozycjach parzystych, jednocześnie swobodnie generując wyrazy na pozycjach nieparzystych. W związku z tym możemy:
1. Wypełnić pozycje parzyste według podanych słów.
2. Następnie, dla każdej pozycji nieparzystej, losować wyraz, przy czym stosujemy 2-gramy i 3-gramy, które pasują zarówno do poprzedniego, jak i następnego wyrazu.
3. W ten sposób budujemy tekst iteracyjnie, który spełnia warunek na pozycjach parzystych, przy jednoczesnym tworzeniu zgodności z modelem N-gramowym.

### c) Losowanie niezbyt długiego tekstu o zadanym pierwszym i ostatnim słowie

Tutaj tekst musi spełniać warunek na początku i końcu, dlatego możemy zastosować następujący algorytm:
1. Rozpocząć generowanie tekstu od ustalonego pierwszego słowa.
2. Kontynuować losowanie słów, stosując 2-gramy lub 3-gramy, aż do momentu, gdy długość generowanego tekstu zbliży się do wymaganej.
3. Następnie, mając na uwadze, że tekst powinien kończyć się ustalonym słowem, dopasowujemy końcowe słowa, aby połączyć końcowe N-gramy z wymaganym ostatnim słowem.
4. W ten sposób proces generowania jest kontrolowany, aby utrzymać zgodność z modelowaniem N-gramowym, a jednocześnie spełnić warunki na początku i końcu tekstu.

### d) Dla listy napisów \([s_1, \dots, s_n]\) losuj tekst o długości \( n \), taki, że \( i \)-te słowo ma sufiks \( s_i \)

Dla tego przypadku, w którym każde \( i \)-te słowo ma określony sufiks \( s_i \), możemy zastosować następującą strategię:
1. Ustalić każde \( i \)-te słowo na liście tak, aby spełniało wymóg posiadania sufiksu \( s_i \).
2. Następnie wypełniać pozostałe pozycje między słowami losowanymi zgodnie z regułami 2-gramów lub 3-gramów.
3. Możemy używać N-gramów, aby wybierać wyrazy na każdej pozycji tak, by tworzyły one płynne przejścia między słowami, a jednocześnie kończyły się na wymaganym sufiksie dla każdej pozycji \( i \).

Tego rodzaju podejście, zamiast sekwencyjnego generowania od początku do końca, znacznie zwiększa szanse na szybkie wygenerowanie tekstu spełniającego wymagania, bez potrzeby wielokrotnego powtarzania całego procesu.

## Zadanie 4
"Wytrenowaliśmy model od tyłu aby lepiej rozumiał wpływu słów początkowych na kontekst końcowego tekstu"

## Zadanie 5
Możemy powiedzieć modelowi żeby każdy wyraz zaczynał się na kolejne litery naszej wiadomości

## Zadanie 6
w oczywisty sposób nie spełnia

alternatywa to używanie modelu z temperaturą 0 jako funkcji haszującej

jeśli ustalimy zdanie klucz, i mały zbiór wyrazów jako słownik, możemy generować tekst jako klucz + pare słów,

wtedy aby odszywrować tekst należy uży brutforce i znaleść ciąg który generuje to samo wyjście

## Zadanie 7
możemy liczyć ciąg prawdopodobieństw tekstu

aby odzyskać tekst potrzebujemy pierwszy wyraz, a potem wybierać tokeny o odpowiednim prawdopodobnie

## Zadanie 8
jesli dodamy spacje na końcu prefiksu papuga zwróci pierwszy token bez spacji, a ponieważ tokenizer przykleja spacje na początku tokenów zaczynających slowa, dostaniemy ograniczony zbiór tokenów

## Zadanie 10
generowanie melodii,

alfabet to nuty, dla uproszczenia pomijamy długość nut

korpus to utwory z danego gatunku muzycznego
