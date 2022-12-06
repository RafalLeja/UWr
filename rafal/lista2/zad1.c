#include <stdio.h>


int dlugosc(char wyraz[]){
    int i = 0;
    while (wyraz[i] != '\0')
    {   
        i++;
    }
    return i;
    
}

int main(int argc, char *argv[])
{
    int Dl;
    if (argc > 3){
        printf("podaj maksymalnie jeden argument\n");
        return 0;
    }
    if (argc > 1){
        Dl = dlugosc(argv[1]);
    }
    int wpis = getchar();
    int litera= 1;
    int koniec = 0;
    while (wpis != EOF) // while((c = getchar()) != EOF) {.... continue; ...}
    {
        if (wpis == '\0')
        {
            return 0;
        }
        int filtr = 0;
        for (int i = 0; i < Dl; i++)
        {
            if (wpis == argv[1][i])
            {
                filtr = 1;
            }
        }
        if (wpis == '\n' && litera == 1)
        {
            wpis = '\0';
            litera = 0;
        }
        
        if (wpis < 32 && wpis >= 127)
        {
            wpis = '\0';
        }
        
        if (filtr != 1)
        {
            if (litera == 1 && wpis == 32)
            {
                wpis = '\0';
                litera = 0;
            }
            if (wpis == 32 || wpis == '\n')
            {
                litera = 0;
            }
            
            if (litera == 1 && (wpis >= 97 && wpis <= 122))
            {
                wpis = wpis - 32;
            }
            
            
            if (wpis == 46 || wpis == 33 || wpis == 63)
            {
                printf("%c", wpis);
                koniec = 1;
            } else {
                if (koniec == 1)
                {
                    printf("\n");
                    koniec = 0;
                    litera = 0;
                }
                printf("%c", wpis);
                
            }
            wpis = getchar();
            filtr = 0;
            litera++;
        } else {
            wpis = getchar();
        }
    }
    
    return 0;
}
