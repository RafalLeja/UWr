### Dane:
- lat RAM = 70ns
- lat L1 = 0.66ns
- size L1 = 2 KiB
- miss L1 = 8%
- lat L2 = 5.62ns
- size L1 = 1 MiB
- miss L1 = 0.5%
- dostęp do pamięci: 36%


Średni czas dostępu do procesora tylko z pamięcią podręczną L1:
$$t_{\text{avg}} = \text{wsp. trafien} \times \text{czas L1} + \text{wsp. chybien} \times (\text{czas L1 + czas pamieci glownej}) =\\
= 0.92 \cdot 0.66 ns + 0.08 \cdot (0.66 ns + 70ns) = 6.22 ns = 9.5 \text{ cykli}$$

Średni czas dostępu do procesora z pamięcią podręczną L1 i L2 (wzór analogiczny do powyższego, uwzględniamy jezscze dostęp do L2):
$$t_{\text{avg}} = 0.92 \cdot 0.66ns + 0.08 \cdot 0.995 \cdot (0.66 ns + 5.62 ns) + \\ + 0.8 \cdot 0.005 \cdot (0.66 ns + 5.62 ns + 70 ns) = 1.41 ns = 2.14 \text{ cykli}$$

**CPI** *(ang. clocks per instruction)* to jeden z aspektów określających wydajność procesora, określa on liczbę potrzebnych cykli zegarowych na wykonanie instrukcji.

CPI dla pamięci podręcznej L1:
$$CPI_{L1} = \text{wsp. instrukcji} \times \frac{\text{ilosc cykli}}{\text{instrukcja}} + \text{wsp. dostepow do pamieci} \times t_{\text{avg} (L1)} = \\
= 0.64 \cdot 1 + 0.36 \cdot 9.5 \approx 4.06 \text{ cykli}$$

CPI dla pamięci podręcznej L1 z L2 (wzór identyczny jak wyżej):
$$CPI_{L1 + L2} = 0.64 \cdot 1 + 0.36 \cdot 2.14 \approx 1.41 \text{ cykli}$$