### memory aliasing:
 - dwa lub więcej wskaźników na te same miejsce w pamięci

```C
void swap(long *xp, long *yp) {
  *xp = *xp + *yp; /* x+y */
  *yp = *xp - *yp; /* x+y-y = x */
  *xp = *xp - *yp; /* x+y-x = y */
}

void swap2(long *xp, long *yp) {
  long x = *xp, y = *yp;
  x = x + y, y = x - y, x = x - y;
  *xp = x, *yp = y;
}
```

#### Odwołując się do pojęcia aliasingu pamięci (ang. memory aliasing) wytłumacz czemu kompilator nie może zoptymalizować poniższej procedury do procedury «swap2»?

- Ponieważ gdyby *xp i *yp wzkazywały na tą samą wartość = 1, to wynikiem swap2 będzie <1,1> a swap <0,0>

####  Pomóż mu zoptymalizować «swap» posługując się słowem kluczowym «restrict» i wyjaśnij jego znaczenie.

 - Słowo kluczowe restrict mówi kompilatorowi że pamięć pod danym adresem jest osiągalna tylko przez ten wzkaźnik, co w naszym przypadku oznacza że *xp i *yp wzkazują na różne adresy