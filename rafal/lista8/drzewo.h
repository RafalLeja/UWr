typedef struct {
  char* name;
  Drzewo* store; 
  int size;
  int ilosc;  
  int capacity;
} * Drzewo;

Drzewo newDrzewo();
void delDrzewo(Drzewo drzewo);
int pushDrzewo(Drzewo drzewo, char* slowo); 
//char popDrzewo(Drzewo drzewo);