
typedef struct list{
    int val;
    struct list * next;
} list;

list * nowaLista(int val);

void delLista(list * lista);

void dodajElement(list * lista, int elem);

void dodajListe(list * odbr, list * zrdl);

int sprawdz(list * lista, int elem);

void wypisz(list * lista);

