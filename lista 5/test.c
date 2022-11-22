#include <stdio.h>

typedef long long Word;

Word new_word(char *from){
    Word result = 0;
    char* addr = (char*) &result;
    for (int i = 0; i < 8; i++)
    {
        if (from[i] == '\0') {
            break;
        }
        addr[i] = from[i];
    }
    return result;
}

char* to_string(Word w){
    char* wynik = (char*) &w; 
    wynik -= 9;
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
        }else{
        l = addr[i];
        printf("%c", l);
        }
    }
}

// Word splice(Word w, Word v){
//     Word wynik;
//     char* addr = (char*) &wynik;
//     char* parz = (char*) &w;
//     char* nie = (char*) &v;
//     for (int i = 0; i < 8; i++)
//     {
//         switch (i%2)
//         {
//         case 0:
//             addr[i] = parz[i/2];
//             break;
        
//         case 1:
//             addr[i] = nie[((i-1)/2)];
//             break;

//         default:
//             break;
//         }
//     }
//     return wynik;
// }

int main (void) {
  Word raz = new_word("OtloOOOO");
  Word dwa = new_word("rain man");
  printf("%llx\n%llx %llu\n", raz, dwa, sizeof (long));
  //char* trzy = to_string(splice(raz, dwa));
  println(raz);
  //printf("\n%s\n", to_string(raz));
  println(dwa);
  //printf("%s\n", trzy);
  return 0;
}