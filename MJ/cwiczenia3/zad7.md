## Omawiany na wykªadzie algorytm BPE dziaªaª zwi¦kszaj¡c liczb¦ tokenów do po»¡danego progu. Zaproponuj algorytm dziaªaj¡cy w drug¡ stron¦, to znaczy startuj¡cy od bardzo du»ej liczby tokenów i zmniejszaj¡cy j¡, a» osi¡gniemy wymagan¡ liczb¦. Algorytm powinien:
-  By¢ niezale»ny od j¦zyka (zatem nie mo»e wykonywa¢ »adnego wst¦pnego szukania wyrazów)
-  Pracowa¢ na du»ym korpusie, pami¦taj¡c bie»¡c¡ tokenizacj¦ korpusu, wykonan¡ za pomoc¡
- dost¦pnych tokenów.
-  Wykonywa¢ wiele kroków, stopniowo zbli»aj¡c si¦ do docelowej wielko±ci sªownika.
-  Usuwa¢ mniej u»yteczne tokeny (czyli tokenizowa¢ tokeny w korpusie)
-  Stara¢ si¦ maksymalizowa¢ unigramowe prawdopodobie«stwo korpusu, czyli QN i=1 p(wi), gdzie wszysktie wi nale»¡ do bie»¡cego zbioru tokenów, a ich konkatenacja to caªy korpus. Przy czym prawdopodobie«stwa szacujemy na podstawie tokenizowanego korpusu. Zastanów si¦ ponadto, dlaczego wymaganie z tego punktu jest sensowne.

Szukamy najrzadszego tokenu, który możemy rozbić na dwa tokeny, tak aby zwiększyć prawdopodobieństwo unigramowe korpusu. Następnie powtarzamy ten proces aż do osiągnięcia wymaganej liczby tokenów.