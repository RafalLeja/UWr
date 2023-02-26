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

double dist(double lat1, double lon1, double lat2, double lon2);
void joinPoint(point** list, point* newElement);
void createPoint(point** list, double lat, double lon, double ele, char time[20]);
void joinKilometer(kilometer** list, kilometer* newElement);
int time2sec(char timeStr[19]);
void creatKilometer(kilometer** list, int number, double lat, double lon, char start[20], char end[20]);
void timeConverter(char* inputTime);
point* getData(char* filePath);
void show(point* list);
customTime setMyTime(int seconds);
properties getProperties(point* list);
kilometer* splitTrack(point* list);
void showProp(properties prop);
void showKilo(kilometer* kilo);