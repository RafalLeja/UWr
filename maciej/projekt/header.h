typedef struct point;
typedef struct customTime;
typedef struct properties;

double dist(double lat1, double lon1, double lat2, double lon2);
void join(point** list, point* newElement);
void createPoint(point** lista, double lat, double lon, double ele, char time[20]);
point* getData(char* filePath);
void show(point* list);
int time2sec(char timeStr[19]);
void timeConverter(char* inputTime);
customTime setMyTime(int seconds);
properties getProperties(point* list);
void showProp(properties prop);