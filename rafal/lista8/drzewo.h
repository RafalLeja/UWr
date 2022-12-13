//typedef struct Drzewo *Drzewo;
typedef struct tree{
  struct tree **store; 
  char* name;
  int size;
  int ilosc;  
  int capacity;
} * Drzewo;


Drzewo newDrzewo();
void delDrzewo(Drzewo drzewo);
void pushDrzewo(Drzewo drzewo, char* slowo); 
//char popDrzewo(Drzewo drzewo);