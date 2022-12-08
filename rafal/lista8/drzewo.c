#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "drzewo.h"

#define defaultCapacity 26

Drzewo newDrzewo() {
  Drzewo drzewo = malloc(sizeof(Drzewo));
  drzewo->name = "";
  drzewo->store = (Drzewo* ) malloc(defaultCapacity * sizeof(Drzewo));
  drzewo->size = 0;
  drzewo->ilosc = 0;
  drzewo->capacity = defaultCapacity;
  return drzewo;
}

void delSlowo(Drzewo drzewo) {
  free(drzewo->store);
}

int pushDrzewo(Drzewo drzewo, char* slowo){
  if (srtlen(slowo) == 0 || slowo == NULL)
  {
    drzewo->ilosc++;
    return 1;
  }
  if (drzewo->store[slowo[0] - 'A'] == NULL)
  {
    drzewo->store[slowo[0] - 'A'] = newDrzewo();
    drzewo->store[slowo[0] - 'A']->name = slowo[0];
  }
  slowo++;
  pushDrzewo(drzewo->store[slowo[0] - 'A'], slowo);
  drzewo->size++;
  
  return 0;
}

