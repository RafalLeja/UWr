#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "drzewo.h"

#define defaultCapacity 26

Drzewo newDrzewo() {
  Drzewo drzewo = (Drzewo) calloc(1, sizeof(struct tree_t));
  if (drzewo == NULL)
  {
    printf("brak pamieci");
    return NULL;
  }
  drzewo->store = (Drzewo*) calloc(defaultCapacity , sizeof(Drzewo));
    if (drzewo->store == NULL)
  {
    printf("brak pamieci");
    return NULL;
  }
  drzewo->name = strdup("");
  
  return drzewo;
}

void delDrzewo(Drzewo drzewo) {
  for (int i = 0; i < 26; i++)
  {
    if (drzewo->store[i] == NULL)
    {
      continue;
    }
      delDrzewo(drzewo->store[i]);
  }
  free(drzewo);    
  return;
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
    drzewo->size++;
  }
  char * bbbb = strdup("");
  strncat(bbbb, slowo+1, strlen(slowo)-1);
  pushDrzewo(drzewo->store[slowo[0] - 'A'], bbbb);
  free(bbbb);
  
  return;
}

void printDrzewo(Drzewo drzewo, char * slowo){
  if(slowo[0] == '\0'){
    slowo = strdup("");
  }
  strncat(slowo, drzewo->name, 1);
  if (drzewo->ilosc > 0 && slowo[0] != '\0')
  {
    printf("%s x %d\n", slowo, drzewo->ilosc);
  }
  for (int i = 0; i < 26; i++)
  {
    if (drzewo->store[i] == NULL)
    {
      continue;
    }
    char * nastepneSlowo = strdup("");
    strcpy(nastepneSlowo, slowo);
    printDrzewo(drzewo->store[i], slowo);
    free(nastepneSlowo);
  }
    
  free(slowo);
  return;
} 

