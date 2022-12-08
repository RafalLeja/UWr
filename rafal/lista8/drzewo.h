//typedef struct Drzewo *Drzewo;
typedef struct DrzewoT {
  char* name;
  Drzewo * store[26]; 
  int size;
  int ilosc;  
  int capacity;
} * Drzewo;

Drzewo newDrzewo();
void delDrzewo(Drzewo drzewo);
int pushDrzewo(Drzewo drzewo, char* slowo); 
//char popDrzewo(Drzewo drzewo);