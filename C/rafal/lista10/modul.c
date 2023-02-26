#include <stdio.h>
#include <stdlib.h>
#include "modul.h"

list * nowaLista(int elem){
    list *out = (list*) malloc(sizeof(list));
    out->val = elem;
    out->next = NULL;
    return out;
}

void delLista(list * lista){
    if (lista->next == NULL)
    {
        free(lista);
    }else {
        delLista(lista->next);
    }
    return;
}

void dodajElement(list * lista, int elem){
    if (lista->next == NULL)
    {
        lista->next = nowaLista(elem);
    }else {
        dodajElement(lista->next, elem);
    }
    return;
}

void dodajListe(list * odbr, list * zrdl){
    if (odbr->next == NULL)    
    {
        odbr->next = zrdl;
    }else{
        dodajListe(odbr->next, zrdl);
    }
    return;
}

int sprawdz(list * lista, int elem){
    if (lista->val == elem)
    {
        return 1;
    }else if (lista->next != NULL) {
        return sprawdz(lista->next, elem);
    }else{
        return 0;
    }
    
}

void wypisz(list * lista){
    if (lista->next == NULL)
    {
        printf("%d\n", lista->val);
    }else
    {
        printf("%d\n", lista->val);
        wypisz(lista->next);
    }
    return;    
}

