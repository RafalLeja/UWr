## Przeczytaj opis baseline solution dla zadania https://2021.poleval.pl/tasks/task4 (odpowiadania na pytania). Spróbuj uzasadni¢, dlaczego to miaªoby dziaªa¢ i zaproponuj jak¡±, sensown¡ wg Ciebie, korekt¦ tego algorytmu.

1. Split the question into tokens using spaCy (model pl_core_news_sm) and ignore the one-character tokens,
2. Send the space-separated tokens as a query to the Search API of the Polish Wikipedia,
3. For each of the returned articles:
    1. Split its title into tokens with spaCy,
    1. If none of the tokens of the title has at least 50% overlap (measured as in Evaluation) with any of the tokens of the question:
    1. remove the part of the title starting from `(`, if found
    4. return the title as an answer,
    5. Otherwise, continue to the next result,
4. If no answer is found at this point, remove the first of the question tokens and jump back to (2).

### Uzasadnienie
wiele pytań używa rzadkich słów, które często są charakterystyczne dla danej dziedziny, okresu historycznego itp. Wyszukiwanie po tych słowach najprawdopodobniej zwróci artykuły, które zawierają odpowiedź na pytanie.

### Korekta
1. Przeszukiwanie po treści artykułów, a nie tylko po tytułach.
2. Użycie Readera do znalezienia odpowiedzi w tekście artykułu.
3. Różne algorytmy do różnych typów pytań (np. dla pytań o daty użyć algorytmu do ekstrakcji dat).