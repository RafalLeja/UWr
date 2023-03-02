#include<stdio.h>
#include<stdlib.h>

typedef struct elem{
    int val;
    struct elem *next;
}elem;

elem* nowaLista(int value){
    elem *pom = (elem*) malloc(sizeof(elem));
    pom->val = value;
    pom->next = NULL;
    return pom;
}

void wypisz(elem * lista){
    printf("%d\n", lista->val);
    if (lista->next != NULL)
    {
        wypisz(lista->next);
    }
    return;    
}

void dodaj(elem* lista, int value){ //zad1
    if (lista->next == NULL)
    {
        lista->next = nowaLista(value);
    }else {
        dodaj(lista->next, value);
    }
    return;
}

void usunOstatni(elem* lista){ //zad2
    if (lista->next->next == NULL)
    {
        free(lista->next);
        lista->next = NULL;
    }else {
        usunOstatni(lista->next);
    }
    return;
}

void dodajListe(elem* odbr, elem* zrdl){ //zad3
    if(odbr == NULL){
        odbr = zrdl;
    }else if (odbr->next == NULL)    
    {
        odbr->next = zrdl;
    }else{
        dodajListe(odbr->next, zrdl);
    }
    return;
}

void usunVal(elem* lista, int value){ //zad4
    if (lista->next == NULL && lista->val == value)
    {
        free(lista);
        lista = NULL;
        return;
    }
    if (lista->next->val == value)
    {
        elem * usun = lista->next;
        lista->next = lista->next->next;
        free(usun);
    }
    if(lista->val == value){
        lista = lista->next; 
    }
    if (lista->next->next != NULL) {
        usunVal(lista->next, value);
    }
    return;
}

void wypiszOdKonca(elem* lista){ //zad6
    if(lista->next != NULL){
        wypiszOdKonca(lista->next);
        printf("%d\n", lista->val);
    }else {
        printf("%d\n", lista->val);
    }
    return;
}

void odwroc(elem** lista){ //zad7
    elem* poprzedni = NULL;
    elem* obecny = *lista;
    elem* nastepny;

    while(obecny != NULL){
        nastepny = obecny->next;
        obecny->next = poprzedni;
        poprzedni = obecny;
        obecny = nastepny;
    }
    *lista = poprzedni;
}

// void rozdziel(elem* lista, elem** dodatnie, elem** ujemne){ //zad8
//     for(elem* licznik = lista; licznik != NULL; licznik = licznik->next){
//         if(licznik->val > 0){
//         }
//         else if(licznik->val < 0){        
//         }
//     }
// }

int main(){
    elem* lista = nowaLista(1);
    // elem* dodatnie = NULL;
    // elem* ujemne = NULL;
    // elem* lista2 = NULL;

    dodaj(lista, 10); dodaj(lista, -5); dodaj(lista, 7); dodaj(lista, -6); dodaj(lista, 1); dodaj(lista, 3);
    // dodaj(lista2, 3); dodaj(lista2, 2);
    // dodajListe(lista, lista2);
    // wyswietl(lista);
    // usunOstatni(lista);
    // usunVal(lista, 5);
    // wypiszOdKonca(lista);
    //odwroc(&lista);
    usunVal(lista, 1);
    wypisz(lista);
    //wypiszOdKonca(lista);

    return 0;
}