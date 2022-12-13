#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "drzewo.h"

#define defaultCapacity 26

Drzewo newDrzewo() {
  Drzewo drzewo = malloc(sizeof(Drzewo));
  drzewo->store = (Drzewo*) malloc(defaultCapacity * sizeof(Drzewo));
  drzewo->name = "";
  drzewo->size = 0;
  drzewo->ilosc = 0;
  drzewo->capacity = defaultCapacity;
  return drzewo;
}

void delSlowo(Drzewo drzewo) {
  free(drzewo->store);
}

void pushDrzewo(Drzewo drzewo, char* slowo){
  if (strlen(slowo) == 0)
  {
    drzewo->ilosc++;
    return;
  }
  if (drzewo->store[slowo[0] - 'A'] == NULL)
  {
    drzewo->store[slowo[0] - 'A'] = newDrzewo();
    strncat(drzewo->store[slowo[0] - 'A']->name, slowo, 1);
  }
  //slowo++;
  char * bbbb = "";
  memmove(bbbb, slowo+1, strlen(slowo)-1);
  pushDrzewo(drzewo->store[slowo[0] - 'A'], bbbb);
  drzewo->size++;
  
  return;
}

void printDrzewo(Drzewo drzewo){
  if(drzewo == NULL){
    return;
  }

  if (drzewo->ilosc > 0)
  {
    printf("%s x %d", drzewo->name, drzewo->ilosc);
    for (int i = 0; i < 26; i++)
    {
      if (drzewo->store[i] == NULL)
      {
        continue;
      }
      
      printDrzewo(drzewo->store[i]);
    }
    
  }
  
} 

