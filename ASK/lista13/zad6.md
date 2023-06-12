### Czasami procesor nie może przeprowadzić translacji dla adresu wygenerowanego w trakcie wykonywania instrukcji. Wymień co najmniej cztery przypadki wykonania  instrukcji «mov», dla których procesor zgłosi wyjątek błędu dostępu do pamięci

1. Próba odczytu lub zapisu do adresu, który nie jest zmapowany do fizycznego obszaru pamięci. Na przykład, jeśli program próbuje uzyskać dostęp do pamięci, która nie została przydzielona lub nie jest dostępna w danym kontekście.

2. Próba zapisu do chronionego obszaru pamięci (np. pamięć tylko do odczytu). Jeśli program próbuje zmodyfikować dane w obszarze pamięci, który jest oznaczony jako chroniony przed zapisem, procesor zgłosi błąd dostępu.

3. Próba odczytu lub zapisu do adresu, który jest poza zakresem dostępnym dla programu. Na przykład, jeśli program próbuje uzyskać dostęp do pamięci poza zaalokowanym obszarem bufora.

4. Próba odczytu lub zapisu do nieprawidłowo wyrównanego adresu. Niektóre procesory wymagają, aby dane były wyrównane do określonej granicy adresowej. Jeśli dane nie są poprawnie wyrównane, procesor zgłosi błąd dostępu.

###  Które z wymienionych przypadków zawsze spowodują zakończenie programu z błędem?

 - Spośród wymienionych przypadków, przypadki 1 i 3 zawsze spowodują zakończenie programu z błędem. Próba dostępu do nieprawidłowego lub niezmapowanego adresu oznacza poważny problem i nie można kontynuować normalnego wykonywania programu.

### Za co odpowiada procedura obsługi błędu strony (ang. page fault)?

- Procedura obsługi błędu strony (page fault) jest mechanizmem używanym w systemach operacyjnych w celu obsługi sytuacji, gdy program próbuje uzyskać dostęp do strony pamięci wirtualnej, która nie jest obecnie załadowana do pamięci fizycznej. 

### Co się dzieje przed i po wykonaniu tej procedury?

- Gdy procesor stwierdza, że wystąpił błąd strony, zgłasza ten fakt do systemu operacyjnego. Procedura obsługi błędu strony jest odpowiedzialna za załadowanie brakującej strony do pamięci fizycznej i odpowiednie skonfigurowanie mapowania pomiędzy adresem wirtualnym a fizycznym. Po wykonaniu procedury obsługi błędu strony program jest wznawiany i instrukcja "mov" może być wykonana bez zgłaszania błędu dostępu do pamięci, o ile warunki dostępu zostały naprawione.