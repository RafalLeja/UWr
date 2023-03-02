#include<stdio.h>
#include<stdlib.h>

typedef struct elem{
    int val;
    struct elem *next;
}elem;

elem* utworz(int val){
    elem *pom = (elem*) malloc(sizeof(elem));
    pom->val = val;
    pom->next = NULL;
    return pom;
}

void wyswietl(elem** lista){
    for(elem* licznik = *lista; licznik != NULL; licznik = licznik->next){
        printf("%d\n", licznik->val);
    }
}

void dodaj(elem** lista, int val){ //zad1
    if(*lista == NULL){
        *lista = utworz(val);
    }

    else{
        for(elem* licznik = *lista; licznik != NULL; licznik = licznik->next){
            if(licznik->next == NULL){
                licznik->next = utworz(val);
                break;
            }
        }
    }
}

void usunOstatni(elem** lista){ //zad2
    for(elem* licznik = *lista; licznik != NULL; licznik = licznik->next){
        if(licznik->next->next == NULL){
            licznik->next = NULL;
        }
    }
}

void dodajListe(elem** lista, elem** lista2){ //zad3
    if(*lista == NULL){
        *lista = *lista2;
    }

    else{
        for(elem* licznik = *lista; licznik != NULL; licznik = licznik->next){
            if(licznik->next == NULL){
                licznik->next = *lista2;
                break;
            }
        }
    }
}

void usunVal(elem** lista, int usun){ //zad4
    elem* poprzedni = NULL;
    for(elem* licznik = *lista; licznik != NULL; licznik = licznik->next){
        if(licznik->val == usun){
            if(poprzedni != NULL){
                poprzedni->next = licznik->next;
            }
            else{
                *lista = licznik->next;
            }
        }
        else{
            poprzedni = licznik;
        }
    }
}

void wypiszOdKonca(elem* lista){ //zad6
    while(lista->next != NULL){
        wypiszOdKonca(lista->next);
        printf("%d\n", lista->val);
        break;
    }
    if(lista->next == NULL){
        printf("%d\n", lista->val);
    }
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
    elem* lista = NULL;
    // elem* dodatnie = NULL;
    // elem* ujemne = NULL;
    // elem* lista2 = NULL;

    dodaj(&lista, 10); dodaj(&lista, -5); dodaj(&lista, 7); dodaj(&lista, -6); dodaj(&lista, 5); dodaj(&lista, 3);
    // dodaj(&lista2, 3); dodaj(&lista2, 2);
    // dodajListe(&lista, &lista2);
    // wyswietl(lista);
    // usunOstatni(&lista);
    // usunVal(&lista, 5);
    // wypiszOdKonca(lista);
    //odwroc(&lista);
    wyswietl(&lista);

    return 0;
}