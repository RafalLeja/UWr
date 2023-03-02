#include<stdio.h>
#include<stdlib.h>

typedef struct elem{
    struct elem *prev;
    int val;
    struct elem *next;
}elem;

elem* utworz(int val){
    elem *pom = (elem*) malloc(sizeof(elem));
    pom->prev = NULL;
    pom->val = val;
    pom->next = NULL;
    return pom;
}

void dodaj(elem* lista, int elem){ //zad1
    if(lista == NULL){
        lista = utworz(elem);
        lista->val = elem;
    }else if(lista->next == NULL) {
        lista->next = utworz(elem);
        lista->next->prev = lista;
    }else
    {
        dodaj(lista->next, elem);
    }
    
    
}

void usunPoczatek(elem* lista){ //zad1
    if(lista == NULL){
        return;
    }else if(lista->next == NULL) {
        free(lista);
        return;
    }else
    {
        lista = lista->next;
        lista->prev = NULL;
        return;
    }
    
}

void usunKonec(elem* lista){
    if(lista == NULL){
        return;
    }else if (lista->next == NULL)
    {
        free(lista);
        return;
    }else if(lista->next->next == NULL) {
        free(lista->next);
        lista->next = NULL;
        return;
    }
    usunKonec(lista->next);
}

void wypisz(elem* lista){
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

int main(){
    elem * lista = utworz(1);
    for (int i = 2; i < 5; i++)
    {
        dodaj(lista, i);
    }
    usunPoczatek(lista);
    wypisz(lista);
    return 0;
}