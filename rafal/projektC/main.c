#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define aproxItr 1500

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

void inputSequence(int argc, char const *argv[], Specs * param);

int includedInSet(Point p, int w, int h, double scale, Point focus);

Point imaginarySq(Point p);

int main(int argc, char const *argv[])
{
    Specs param = { 0, 0, "mandel-", 0.75, 10, {-35, 0} };
    inputSequence(argc, argv, &param);
    printf("w = %d, h = %d, pre = %s, zoom = %f, frames = %d, fx = %f, fy = %f\n", param.width, param.height, param.nameprefix, param.zoom, param.maxframes, param.focus.x, param.focus.y);
    double scale = 1;
    Point offset = {0, 0};
    for (int i = 0; i < param.maxframes; i++)
    {
        char * name = strdup(param.nameprefix);
        char * number = strdup("");
        sprintf(number, "%d", i);
        name = strcat(name, number);
        name = strcat(name, ".pgm");
        FILE * plik = fopen(name, "wb");
        fprintf(plik, "P2\n");
        fprintf(plik, "%d %d\n", param.width, param.height);
        fprintf(plik, "255\n");
        for (int y = 0; y < param.height; y++)
        {
            // if (y % 1000 == 0)
            // {
            //     printf("%d\n", y);
            // }
            
            for (int x = 0; x < param.width; x++)
            {
                Point pixel = {x, y};
                if (includedInSet(pixel, param.width, param.height, scale, offset) == 1)
                {
                    fprintf(plik, "255 ");
                }else {
                    fprintf(plik, "0 ");
                }
            }
            fprintf(plik, "\n");
        }
        fclose(plik);
        offset.x += param.focus.x*scale;
        offset.y += param.focus.y;
        scale *= param.zoom;
    }
    
    return 0;
}

Point imaginarySq(Point p){
    Point o = { pow(p.x, 2) - pow(p.y, 2), 2*p.x*p.y};
    return o; 
}

int includedInSet(Point p, int w, int h, double scale, Point focus){
    double const minX = -2.5, maxX = 1.5, minY = -1.25, maxY = 1.25;
    Point imaginaryPoint;
    imaginaryPoint.x = ((p.x+focus.x) * (fabs(minX - maxX)/w) + minX)*scale;
    imaginaryPoint.y = ((p.y+focus.y) * (fabs(minY - maxY)/h) + minY)*scale;
    //printf("%f %f \n", imaginaryPoint.x, imaginaryPoint.y);
    Point z = {0, 0};
    for(int i = 0; i<aproxItr && sqrt(pow(z.x,2)+ pow(z.y,2)) < 2; i++){
        //printf("%f %f \n", z.x, z.y);
        Point sqr = imaginarySq(z);
        z.x = sqr.x + imaginaryPoint.x;
        z.y = sqr.y + imaginaryPoint.y; 
    }
    if (sqrt(pow(z.x,2)+ pow(z.y,2)) >= 2)
    {
        return 0;
    }
    return 1;
    
}

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
            if (strchr(argv[i], ',') == NULL)
            {
                printf("blad parametru --focus X,Y");
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
    if (param->height == 0 && param->width != 0)
    {
        param->height = param->width * 5/8;
    }else if (param->width == 0 && param->height != 0)
    {
        param->width = param->height * 8/5;
    }else if (param->width == 0 && param->height == 0)
    {
        param->width = 1920;
        param->height = 1200;
    }

}