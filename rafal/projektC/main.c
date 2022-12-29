#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct {
  double x;
  double y;
} Point;

typedef struct {
    int width;
    int height;
    char * nameprefix; 
    float zoom;
    int maxframes;
    Point focus;
} Specs;

void inputSequence(int argc, char const *argv[], Specs * param){
    char options[6][15] = {"--width", "--height", "--nameprefix", "--zoom", "--maxframes", "--focus"};
    for (int i = 1; i < argc; i++)
    {
        char option = '\0';
        for (int j = 0; j < 6; j++)
        {
            if (strcmp(argv[i], options[j]) == 0)
            {
                option = options[j][2];
            }
            
        }
        switch (option)
        {
        case 'w':
            i++;
            param->width = atoi(argv[i]);
            break;
        
        case 'h':
            i++;
            param->height = atoi(argv[i]);
            break;
        
        case 'n':
            i++;
            param->nameprefix = strdup("");
            strcpy(param->nameprefix, argv[i]);
            break;
        
        case 'z':
            i++;
            param->zoom = atof(argv[i]);
            break;

        case 'm':
            i++;
            param->maxframes = atoi(argv[i]);
            break;

        case 'f':
            i++;
            int splitIdx = (int) (strchr(argv[i], ',') - argv[i]);
            if (splitIdx == 0)
            {
                printf("blad parametru --focus X,Y");
                exit(1);
            }
            
            char * buff = strdup("");
            strncat(buff, argv[i], splitIdx);
            param->focus.x = atoi(buff);
            param->focus.y = atoi(argv[i]+splitIdx+1);
            free(buff);
            break;
        default:
            break;
        }
    }
    
}

int main(int argc, char const *argv[])
{
    Specs param = { 1800, 1200, "mandel-", 0.25, 10, {sqrt(2)*600, 0} };
    // param.width = 1800;
    // param.height = 1200;
    // param.nameprefix = "mandel-";
    // param.zoom = 0.25;
    // param.focus.x = sqrt(2)*param.width;
    // param.focus.y = 0;

    inputSequence(argc, argv, &param);
    printf("%d %d %s %f %d %f %f", param.width, param.height, param.nameprefix, param.zoom, param.maxframes, param.focus.x, param.focus.y);
    
    return 0;
}
