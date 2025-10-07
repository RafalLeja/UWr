/*
* Rafał Leja 340879
* MIA 2025
* Zadanie A, Lista 1
* 07.10.2025
*/
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
  int input;
  scanf("%d", &input);

  int banknoty [] = { 100, 20, 10, 5, 1 };
  int nominal = 0;
  int ilosc = 0;
  while (input > 0) {
    int akt_ilosc = input / banknoty[nominal];
    if (akt_ilosc > 0){
      ilosc += akt_ilosc;
      input -= akt_ilosc * banknoty[nominal];
    } 

    nominal++;
  }

  printf("%d\n", ilosc);
  return EXIT_SUCCESS;
}
