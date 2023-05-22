 - **magistrala**: zespół linii przenoszących sygnały oraz układów wejścia-wyjścia służących do przesyłania sygnałów między połączonymi urządzeniami w systemach mikroprocesorowych.

  - **przepustowość**: taktowanie zegara magistrali, ilość różnych ustawień bitów w ciągu sekundy

 - **Podkradanie cykli**: polega na tym, że jeśli procesor i DMA chciałyby korzystać z szyny pamięci w tym samym czasie, to DMA ma zawsze większy priorytet i procesor w danym cyklu pamięci będzie przetrzymywany, dopóki szyna się nie zwolni.

  1. (a) 10 000 000 / 2 = 5 000 000
  2. (b) 
  
  
przepustowość magistrali to 40MB/s

przepustowość DMA to 5MB/s

$$5/40 * 100\% = 12.5\%$$

100% + 40%/2 = 70% średnia ilość cykli dostępu do pamięci

70% * 12.5% = 8.75% ilość instrukcji wykorzystanych przez DMA

5 000 000 * 91.25% = 4 562 500 instrukcji wykonanych przez procesor

Zastanów się, co złego mogłoby się stać, gdyby kontroler
dysku dostawał wyłącznie cykle magistrali nieużywane przez procesor?