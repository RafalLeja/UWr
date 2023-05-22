 - **przerwanie**: sygnał przerwania wysłany do procesora informuje go np o ukończeniu pobierania danych z dysku, procesor wtedy przerywa aktualnie wykonywany program, zappisuje stan, i wykonuje procedure przerwania

 - **procedura przerwania**: blok instrukcji przypisany do konkretnego sygnału przerwania, uruchamiany przez ten sygnał np. ruch myszką

 - **konroler DMA**: kontroler umożliwiający niezależne działanie procesora, odciążający go (np. poprzez kopiowanie danych) aby procesor nie wykonywał zbędnych działań, jako że nie ma to za bardzo sensu - procesory są stworzone do bardziej skomplikowanych operacji.

Dane:
 - 300 rpm
 - 512 bajtów/sektor
 - 18 sektorów/ścieżke
 - 80 ścieżek/powierzchnie

 $$T_{\text{avg rotation latency}} = \frac{60[s]/300[r/m] * 1000[ms]}{2} = 200[ms]$$

 $$T_{\text{avg transfer time}} = \frac{T_{\text{avg rotation latency}}}{\text{ilość sektorów}} = 200/18 = 11.1 [ms]$$

 $$T_{\text{czas dla CPU bez DMA}}(n) = n(11.1 - 512 * 0.016) = 2.918[ms]$$

 $$T_{\text{czas dla CPU z DMA}}(n) = n(11.1 - 0.016) = 11.094$$

