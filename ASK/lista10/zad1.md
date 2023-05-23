 - plater: dysk pokryty ferromagnetykiem na którym zapisywane są scieżki, ma dwie powierzchnie

 - głowica: cewka nad powierzchnią odczytująca oraz zapisująca dane na scieżce

 - ścieżka: pierścien znajdujący się na powierzchni, podzielony na sektory, na którym zapisywane są dane

 $$T(0, 576k) = \frac{576000}{24000} = 24[ms] $$

 $$T_{\text{avg seek time}} = \frac{\text{T(0, 576k)}}{3} = 8[ms]$$

 $$T_{\text{avg rotation latency}} = \frac{60[s]/7200[r/m] * 1000[ms]}{2} = 4[ms]$$

 $$T_{\text{avg transfer time}} = \frac{T_{\text{avg rotation latency}}}{\text{ilość sektorów}} = 4/32000 = 0.125 [us]$$

 $$T_{\text{avg access}} = 8 + 4 + 0.000000125 = 12.000000125[ms]





