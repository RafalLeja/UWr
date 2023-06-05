### Predyktor skoków
  - część procesora odpowiedzialna za przewidywanie w którą strone wykona się rozgałęźenie. Predyktor skoków jest używany przez procesor do przewidywania, czy dany skok będzie warunkowy (np. skok jeśli równa się zero) lub niewarunkowy (bezwarunkowy skok). Predyktor skoków podejmuje próbę przewidzenia, czy skok zostanie wykonany na podstawie wcześniejszych obserwacji, takich jak historii skoków w programie. 

### Co musi zrobić, jeśli skok zostanie źle przewidziany?
  - usunąć przewidziane instrukcje i ponownie rozpocząć proces wydawania instrukcji. Jeśli predyktor skoków poprawnie przewiduje skok, procesor kontynuuje wykonanie programu z docelowego miejsca skoku. Jednakże, jeśli skok zostanie źle przewidziany, procesor musi cofnąć się do poprzedniego punktu wykonania i ponownie wykonać instrukcje z prawidłowego miejsca skoku.

```C
void merge1(long src1[], long src2[], long dest[], long n) {
  long i1 = 0, i2 = 0;
  while (i1 < n && i2 < n)
    *dest++ = src1[i1] < src2[i2] ? src1[i1++] : src2[i2++];
}

void merge1(long src1[], long src2[], long dest[], long n) {
  long i1 = 0, i2 = 0;
  while (i1 < n && i2 < n) {
    long val1 = src1[i1];
    long val2 = src2[i2];
    long minVal = (val1 < val2) ? val1 : val2;
    long maxVal = (val1 < val2) ? val2 : val1;
    *dest++ = minVal;
    i1 += (minVal == val1);
    i2 += (minVal == val2);
    *dest++ = maxVal;
  }
}
```