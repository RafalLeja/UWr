#include <stdio.h>
#include <string.h>

#define MAX_N 1000
#define MAX_K 1000

int n, k;
char identifiers[MAX_N][MAX_K];
int max_uniqueness, max_uniqueness_idx;

int main() {
  scanf("%d%d", &n, &k);

  // Wczytaj identyfikatory
  for (int i = 0; i < n; i++) {
    scanf("%s", identifiers[i]);
  }

  // Dla każdego identyfikatora, oblicz jego unikatowość
  for (int i = 0; i < n; i++) {
    // Licznik unikatowych pozycji dla danego identyfikatora
    int uniqueness = 0;

    // Przejdź przez każdą pozycję w identyfikatorze
    for (int j = 0; j < k; j++) {
      // Licznik liczby identyfikatorów, które zawierają tę samą literę na pozycji j
      int count = 0;

      // Przejdź przez wszystkie identyfikatory i sprawdź, czy zawierają tę samą literę
      for (int l = 0; l < n; l++) {
        if (identifiers[l][j] == identifiers[i][j]) {
          count++;
        }
      }

      // Jeśli tylko jeden identyfikator zawiera tę samą literę, oznacza to, że jest on unikatowy
      if (count == 1) {
        uniqueness++;
      }
    }

    // Jeśli unikatowość tego identyfikatora jest większa niż poprzednio znaleziona, zapamiętaj ją i jej indeks
    if (uniqueness > max_uniqueness) {
      max_uniqueness = uniqueness;
      max_uniqueness_idx = i;
    }
  }

  // Wypisz najbardziej unikatowy identyfikator oraz jego unikatowość
  printf("%s\n%d\n", identifiers[max_uniqueness_idx], max_uniqueness);

  return 0;
}