#include <stdio.h>
#include <stdlib.h>
#include "modul.h"

int main()
{
    list * lista = nowaLista(1);
    for (int i = 0; i < 10; i++)
    {
        dodajElement(lista, i+2);
    }
    wypisz(lista);
    printf("%d", sprawdz(lista, 1));
    
    return 0;
}

