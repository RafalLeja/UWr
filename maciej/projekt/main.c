#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#define Pi 3.14159265358979323846
#define deg2rad(deg) ((deg) * Pi / 180.0)
#define earthRadius 6371.0

typedef struct point{
    double lat;
    double lon;
    double ele;
    char time[20];
    struct point* next;
}point;

typedef struct customTime{
    int sec;
    int min;
    int hh;
}customTime;

typedef struct properties{
    char start[20];
    char end[20];
    customTime totalTime;
    double maxSpeed;
    double maxHeight;
    double minHeight;
    double averageSpeed;
    double distance;
    double bestRate;
    double averageRate;
}properties;

typedef struct kilometer{
    int number;
    double lat;
    double lon;
    char start[20];
    char end[20];
    int rate;
    struct kilometer* next;
}kilometer;

double dist(double lat1, double lon1, double lat2, double lon2){
    double dLat = deg2rad(lat2 - lat1);
    double dLon = deg2rad(lon2 - lon1);

    lat1 = deg2rad(lat1);
    lat2 = deg2rad(lat2);

    double a = sin(dLat/2) * sin(dLat/2) + cos(lat1) * cos(lat2) * sin(dLon/2) * sin(dLon/2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a)); 
    
    return earthRadius * c * 1000;
}

void joinPoint(point** list, point* newElement){
    if(*list == NULL){
        *list = newElement;
    }

    else{
        point* last = *list;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = newElement;
    }
}

void createPoint(point** list, double lat, double lon, double ele, char time[20]){
    point* new = (point*)malloc(sizeof(point));
    new->lat = lat;
    new->lon = lon;
    new->ele = ele;
    strcpy(new->time, time);
    new->next = NULL;
    joinPoint(list, new);
}

void joinKilometer(kilometer** list, kilometer* newElement){
    if(*list == NULL){
        *list = newElement;
    }

    else{
        kilometer* last = *list;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = newElement;
    }
}

int time2sec(char timeStr[19]){
    struct tm tm = {0};
    sscanf(timeStr, "%4d-%2d-%2dT%2d:%2d:%2d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday, &tm.tm_hour, &tm.tm_min, &tm.tm_sec);
    tm.tm_year -= 1900;
    tm.tm_mon--;
    time_t time = mktime(&tm);

    return (double) time;
}

void creatKilometer(kilometer** list, int number, double lat, double lon, char start[20], char end[20]){
    kilometer* new = (kilometer*)malloc(sizeof(kilometer));
    new->number = number;
    new->lat = lat;
    new->lon = lon;
    strcpy(new->start, start);
    strcpy(new->end, end);
    new->rate = time2sec(new->end) - time2sec(new->start);
    new->next = NULL;
    joinKilometer(list, new);
}

void timeConverter(char* inputTime){
    int year, month, day, hour, minute, second;
    sscanf(inputTime, "%d-%d-%dT%d:%d:%d", &year, &month, &day, &hour, &minute, &second);
    sprintf(inputTime, "%02d:%02d:%02d %02d.%02d.%04d", hour, minute, second, day, month, year);
}

point* getData(char* filePath){
    FILE *fp = fopen(filePath, "r");
    point* points = NULL;
    point** start = &points;

    if(fp == NULL){
        printf("Blad przy otwieraniu pliku");
        return *start;
    }

    char line[256];
    while(fgets(line, sizeof(line), fp)){
        sscanf(line, " %[^\n]", line);
        if (strncmp(line, "<trkpt ", 7) == 0){
            double lat, lon;
            sscanf(line, "<trkpt lat=\"%lf\" lon=\"%lf\">", &lat, &lon);

            while(strncmp(line, "<ele>", 5) != 0){
                fgets(line, sizeof(line), fp);
                sscanf(line, " %[^\n]", line);
            }

            double ele;
            sscanf(line, "<ele>%lf<", &ele);
        
            while(strncmp(line, "<time>", 6) != 0){
                fgets(line, sizeof(line), fp);
                sscanf(line, " %[^\n]", line);
            }

            char time[20];
            sscanf(line, "<time>%19[^<]</time>", time);

            createPoint(&points, lat, lon, ele, time);
        }
    }

    return *start;
}

void show(point* list){
    for(point* counter = list; counter != NULL; counter = counter->next){
        printf("%f %f %f %s\n", counter->lat, counter->lon, counter-> ele, counter->time);
    }
}

customTime setMyTime(int seconds){
    customTime time;
    time.hh = seconds / 3600;
    time.min = (seconds % 3600) / 60;
    time.sec = seconds % 60;

    return time;
}

properties getProperties(point* list){
    properties prop;

    int line = 1;
    double coords[4];
    int time[2];
    double distance = 0;

    int maxTime[2];
    double maxDist[2];
    maxDist[0] = 0;
    maxDist[1] = 0;

    point* counter = list;

    int timeStart = time2sec(counter->time);
    maxTime[0] = timeStart;
    time[0] = time2sec(counter->time);
    int timeEnd;
    coords[0] = counter->lat;
    coords[1] = counter->lon;
    prop.maxHeight = counter->ele;
    prop.minHeight = counter->ele;
    strcpy(prop.start, counter->time);
    timeConverter(prop.start);


    prop.maxSpeed = 0;
    prop.bestRate = 999;
    counter = counter->next;

    for(; counter != NULL; counter = counter->next){
        if(line % 2 == 0){
            coords[0] = counter->lat;
            coords[1] = counter->lon;
            time[0] = time2sec(counter->time);
            maxTime[1] = time[0];
        }
        else{
            coords[2] = counter->lat;
            coords[3] = counter->lon;
            time[1] = time2sec(counter->time);
            maxTime[1] = time[1];
        }
        distance += dist(coords[0], coords[1], coords[2], coords[3]);
        maxDist[1] += dist(coords[0], coords[1], coords[2], coords[3]);

        if(maxTime[1] - maxTime[0] >= 10){
            if(prop.maxSpeed < (maxDist[1] - maxDist[0]) / (maxTime[1] - maxTime[0]) * 3.6){
                prop.maxSpeed = (maxDist[1] - maxDist[0]) / (maxTime[1] - maxTime[0]) * 3.6;
            }
            if(prop.bestRate > (maxTime[1] - maxTime[0]) / (maxDist[1] - maxDist[0]) / 60 * 1000){
                prop.bestRate = (maxTime[1] - maxTime[0]) / (maxDist[1] - maxDist[0]) / 60 * 1000;
            }

            maxTime[0] = maxTime[1];
            maxDist[0] = maxDist[1];
        }

        if(counter->ele > prop.maxHeight){
            prop.maxHeight = counter->ele;
        }
        else if(counter->ele < prop.minHeight){
            prop.minHeight = counter->ele;
        }

        timeEnd = time2sec(counter->time);
        strcpy(prop.end, counter->time);
        timeConverter(prop.end);

        line++;
    }

    prop.totalTime = setMyTime(timeEnd - timeStart);
    prop.distance = distance;
    prop.averageSpeed = prop.distance / (timeEnd - timeStart) * 3.6;
    prop.averageRate = (timeEnd - timeStart) / prop.distance / 60 * 1000;

    return prop;
}

kilometer* splitTrack(point* list){
    kilometer* kilo = NULL;
    kilometer** begin = &kilo;

    int kiloCounter = 1;
    int line = 1;
    double coords[4];
    char start[20];
    double distance = 0;
    point* counter = list;

    strcpy(start, counter->time);
    coords[0] = counter->lat;
    coords[1] = counter->lon;

    counter = counter->next;

    for(; counter != NULL; counter = counter->next){
        if(line % 2 == 0){
            coords[0] = counter->lat;
            coords[1] = counter->lon;
        }
        else{
            coords[2] = counter->lat;
            coords[3] = counter->lon;
        }
        distance += dist(coords[0], coords[1], coords[2], coords[3]);

        if(distance - 1000 * kiloCounter > 0){
            creatKilometer(&kilo, kiloCounter, coords[line % 2], coords[(line % 2) + 1], start, counter->time);
            
            kiloCounter++;
            strcpy(start, counter->time);
        }

        line++;
    }

    return *begin;
}

void showProp(properties prop){
    printf("start: %s\nend: %s\ntotalTime: %02d:%02d:%02d\nmaxSpeed: %.2f\naverageSpeed: %.2f\nmaxHeight: %.2f\nminHeight: %.2f\ndistance: %.2f[km]\nbestRate: %02d'%02d''\naverageRate: %02d'%02d\n",
    prop.start,
    prop.end,
    prop.totalTime.hh, prop.totalTime.min, prop.totalTime.sec,
    prop.maxSpeed,
    prop.averageSpeed,
    prop.maxHeight,
    prop.minHeight,
    prop.distance / 1000,
    (int) prop.bestRate / 1,
    (int) (prop.bestRate * 60) / 1 % 60,
    (int) prop.averageRate / 1,
    (int) (prop.averageRate * 60) / 1 % 60
    );
}

void showKilo(kilometer* kilo){
    for(kilometer* counter = kilo; counter != NULL; counter = counter->next){
        int seconds = time2sec(counter->end) - time2sec(counter->start);
        printf("%d %02d'%02d''\n", counter->number, seconds / 60, seconds % 60);
    } 
}

int main(int argc, char* argv[]){
    if(argc < 2){
        printf("bledne wywolanie funkcji");
        return 1;
    }

    point* listOfPoints = getData(argv[1]);
    properties prop;
    prop = getProperties(listOfPoints);
    kilometer* kilometers = splitTrack(listOfPoints);

    showProp(prop);
    // showKilo(kilometers);
    
    return 0;
}