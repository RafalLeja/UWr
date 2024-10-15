### Słownik 
* Sierota: aktywny proces którego rodzic zakończył działanie
* Zombie: proces który zakończył działanie, ale jego rodzic nie odczytał jego zwracanej wartości z tablicy procesów
* Stan: Running - Działający, Stopped - Uśpiony, Terminated - Przeznaczony do zniszczenia

### Jak jądro systemu reaguje na sytuację kiedy proces staje się sierotą? 
Proces init adoptuje sierotę. Gdy sierota zakończy działanie jest grzebana przez init.

### W jaki sposób pogrzebać proces, który wszedł w stan zombie?
Trzeba zabić jego rodzica, wtedy stanie się sierotą i zostanie pogrzebany przez init.

### Czemu proces nie może sam siebie pogrzebać?
Żeby pogrzebać proces, trzeba odczytać jego zwracaną wartość.
Żeby otrzymać zwracaną wartość trzeba zakończyć proces.

### Zauważ, że proces może, przy pomocy waitpid(2), czekać na zmianę stanu wyłącznie swoich dzieci. Co złego mogłoby się stać, gdyby znieść to ograniczenie? Rozważ scenariusze (a) dziecko może czekać na zmianę stanu swojego rodzica (b) wiele procesów oczekuje na zmianę stanu jednego procesu.
 - aby dziecko wznowiło działanie, musiało by czekać aż jego rodzic zostanie pogrzebany, więc zostanie zombie
 - gdy program czeka na zmiane stanu, zużywa on pamięć i moc obliczeniową.
  Jeśli wiele procesów czekało by na zmiane jednego procesu mogło by dojść do sytuacji gdzie skończy się pamięć, więc program na który czekają mógłby nie móc zakończyć działania. 