- **pamięć podręczna**: pamięć położona blisko procesora w celu skrócenia czasu dostępu, zawiera kopię często używanych danych z pamięci RAM

| Pamięć | Czas (cykle) | Prawdopodobieństwo |  Suma cykli  |
| ------ | ------------ | ------------------ | ---- |
| L1     | 4            | 90%                |  4   |
| L2     | 12           | 95%                |  12  |
| L3     | 40           | 98%                |  56  |
| DRAM   | 200          | 100%               |  256 |

1 cykl = 0.4[ns]

a)

$$90\%*4 +
\underbrace{10\%}_{\text{nietrafienie}}*95\%*16 +
\underbrace{10\% * 5\%}_{\text{nietrafienie}}*98\%*56 +
\underbrace{10\% * 5\% * 2\%}_{\text{nietrafienie}}*100\%*256 = 5,42\text{ cykli} = 2,168$$

256 * 0.4 = 102.4