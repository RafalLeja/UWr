### Opisz procedur¦, która, wykorzystuj¡c podstawowy interfejs do generacji tekstu modelu j¦zykowego, mo»liwie efektywnie rozwi¡zuje problem generacji dokªadnie jednego wyrazu (dla zadanego preksu, skªadaj¡cego si¦ z peªnych wyrazów).

Kończymy generowanie po pierwszym wyrazie

Z puli k najlepszych tokenów wybieramy pełne słowa, a tylko nie pełne słowa rozwijamy do pełnych słów, po czym dodajemy je do puli i losujemy.
