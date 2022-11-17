#include <stdio.h>
#include <stdlib.h>

typedef long long Word;

Word new_word(char *from){
    Word result = 0;
    char* addr = (char*) &result;
    for (int i = 0; i < 8; i++)
    {
        if (!from[i]) break;
        addr[i] = from[i];
    }
    return result;
}

char* to_string(Word w){
    //Word x= 0;
    char* wynik = (char*) calloc(9, sizeof(char)); 
    char* wyraz = (char*) &w; 
    for (int i = 0; i < 8; i++)
    {
        wynik[i] = wyraz[i];
    }

    return wynik;
}

void println(Word w){
    char* addr = (char*) &w; 
    char l;
    for (int i = 0; i < 8; i++)
    {
        if (addr[i] == '\0')
        {
            printf("\n");
            break;
        }
        l = addr[i];
        printf("%c", l);

    }
    printf("\n");
}

Word splice(Word w, Word v){
    Word wynik = 0;
    char* addr = (char*) &wynik;
    char* parz = (char*) &w;
    char* nie = (char*) &v;
    for (int i = 0; i < 8; i++)
    {
        switch (i%2)
        {
        case 0:
            addr[i] = parz[i/2];
            break;
        
        case 1:
            addr[i] = nie[((i-1)/2)];
            break;

        default:
            break;
        }
    }
    return wynik;
}

int main (void) {
  Word raz = new_word("Otloczyn");
  Word dwa = new_word("rain man");
  Word tmp = splice(raz, dwa);
  char* trzy = to_string(tmp);
  println(raz);
  println(dwa);
  println(splice(raz, dwa));
  printf("%s\n", trzy);
  free(trzy);
  return 0;
}