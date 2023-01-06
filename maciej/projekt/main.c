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

typedef struct myTime{
    int sec;
    int min;
    int hh;
}myTime;

typedef struct properties{
    char start[20];
    char end[20];
    myTime totalTime;
    double maxSpeed;
    double maxHeight;
    double minHeight;
    double averageSpeed;
    double distance;
    // double bestRate;
    double averageRate;
}properties;

double dist(double lat1, double lon1, double lat2, double lon2){
    double dLat = deg2rad(lat2 - lat1);
    double dLon = deg2rad(lon2 - lon1);

    lat1 = deg2rad(lat1);
    lat2 = deg2rad(lat2);

    double a = sin(dLat/2) * sin(dLat/2) + sin(dLon/2) * sin(dLon/2) * cos(lat1) * cos(lat2); 
    double c = 2 * atan2(sqrt(a), sqrt(1-a)); 
    
    return earthRadius * c * 1000;
}

void join(point** list, point* newElement){
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

void createPoint(point** lista, double lat, double lon, double ele, char time[20]){
    point* new = (point*)malloc(sizeof(point));
    new->lat = lat;
    new->lon = lon;
    new->ele = ele;
    strcpy(new->time, time);
    new->next = NULL;
    join(lista, new);
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

int time2sec(char timeStr[19]) {
    struct tm tm = {0};
    sscanf(timeStr, "%4d-%2d-%2dT%2d:%2d:%2d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday, &tm.tm_hour, &tm.tm_min, &tm.tm_sec);
    tm.tm_year -= 1900;
    tm.tm_mon--;
    time_t time = mktime(&tm);

    return (double) time;
}

void timeConverter(char* inputTime){
    int year, month, day, hour, minute, second;
    sscanf(inputTime, "%d-%d-%dT%d:%d:%d", &year, &month, &day, &hour, &minute, &second);
    sprintf(inputTime, "%02d:%02d:%02d %02d.%02d.%04d", hour, minute, second, day, month, year);
}

myTime setMyTime(int seconds){
    myTime time;
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
    point* counter = list;

    int timeStart = time2sec(counter->time);
    time[0] = time2sec(counter->time);
    int timeEnd;
    coords[0] = counter->lat;
    coords[1] = counter->lon;
    prop.maxHeight = counter->ele;
    prop.minHeight = counter->ele;
    strcpy(prop.start, counter->time);
    timeConverter(prop.start);

    prop.maxSpeed = 0;
    counter = counter->next;

    for(; counter != NULL; counter = counter->next){
        if(line % 2 == 0){
            coords[0] = counter->lat;
            coords[1] = counter->lon;
            time[0] = time2sec(counter->time);
        }
        else{
            coords[2] = counter->lat;
            coords[3] = counter->lon;
            time[1] = time2sec(counter->time);
        }
        distance += dist(coords[0], coords[1], coords[2], coords[3]);

        if(dist(coords[0], coords[1], coords[2], coords[3])/ abs(time[1] - time[0]) > prop.maxSpeed){
            prop.maxSpeed = dist(coords[0], coords[1], coords[2], coords[3])/ abs(time[1] - time[0]) * 3.6;
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
    prop.averageRate = (timeEnd - timeStart) / prop.distance /60 * 1000;

    return prop;
}

void showProp(properties prop){
    printf("start: %s\nend: %s\ntotalTime: %02d:%02d:%02d\nmaxSpeed: %f\naverageSpeed: %f\nmaxHeight: %f\nminHeight: %f\ndistance: %.2f[km]\naverageRate: %f",
    prop.start,
    prop.end,
    prop.totalTime.hh, prop.totalTime.min, prop.totalTime.sec,
    prop.maxSpeed,
    prop.averageSpeed,
    prop.maxHeight,
    prop.minHeight,
    prop.distance / 1000,
    prop.averageRate
    );
}

int main(int argc, char* argv[]){
    if(argc < 2){
        printf("bledne wywolanie funkcji");
        return 1;
    }

    point* listOfPoints = getData(argv[1]);

    properties prop;

    show(listOfPoints);
    prop = getProperties(listOfPoints);

    showProp(prop);
    

    return 0;
}