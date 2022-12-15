//typedef struct Drzewo *Drzewo;
typedef struct tree_t{
  struct tree_t ** store; 
  char* name;
  int size;
  int ilosc;  
  int capacity;
} * Drzewo;


Drzewo newDrzewo();
void delDrzewo(Drzewo drzewo);
void pushDrzewo(Drzewo drzewo, char* slowo); 
void printDrzewo(Drzewo drzewo);