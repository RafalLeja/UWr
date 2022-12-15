#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "drzewo.h"

#define defaultCapacity 26

Drzewo newDrzewo() {
  Drzewo drzewo = (Drzewo) calloc(1, sizeof(struct tree_t));
  drzewo->store = (Drzewo*) calloc(defaultCapacity , sizeof(Drzewo));
  drzewo->name = strdup("");
  drzewo->size = 0;
  drzewo->ilosc = 0;
  drzewo->capacity = defaultCapacity;
  if (drzewo->store == NULL)
  {
    printf("brak pamieci");
    return NULL;
  }
  
  return drzewo;
}

void delDrzewo(Drzewo drzewo) {
  free(drzewo->store);
  free(drzewo->name);
}

void pushDrzewo(Drzewo drzewo, char* slowo){
  //printf("%c\n", slowo[0]);
  if (strlen(slowo) == 1)
  {
    drzewo->ilosc++;
    return;
  }
  //printf("%p\n", drzewo->store[slowo[0] - 'A']);
  if (drzewo->store[slowo[0] - 'A'] == NULL)
  {
    //printf("a");
    drzewo->store[slowo[0] - 'A'] = newDrzewo();
    strncat(drzewo->store[slowo[0] - 'A']->name, slowo, 1);
    drzewo->size++;
  }
  char * bbbb = strdup("");
  strncat(bbbb, slowo+1, strlen(slowo)-1);
  pushDrzewo(drzewo->store[slowo[0] - 'A'], bbbb);
  free(bbbb);
  
  return;
}

void printDrzewo(Drzewo drzewo){
  //printf("%s x %d", drzewo->name, drzewo->ilosc);
  if(drzewo == NULL){
    return;
  }
  if (drzewo->ilosc > 0)
  {
    printf("%s x %d\n", drzewo->name, drzewo->ilosc);}
    for (int i = 0; i < 26; i++)
    {
      if (drzewo->store[i] == NULL)
      {
        //printf("brak");
        continue;
      }
      
      printDrzewo(drzewo->store[i]);
    }
    
  
  return;
} 

