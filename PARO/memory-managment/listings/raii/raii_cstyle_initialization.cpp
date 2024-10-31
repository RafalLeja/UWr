#include <pthread.h>
#include <stdio.h>

struct GameData
{
    GameData() : player_level(1) {}

    FILE* save;
    pthread_mutex_t the_mutex;
    int player_level;
};

int main(int argc, char* argv[])
{
    GameData data; // initialization, then
    // stepwise resource acquisition
    if (0 != pthread_mutex_init(&data.the_mutex, NULL))
        return 2;
    data.save = fopen("save.dat", "r");
    if (NULL == data.save)
        return 1;
    return 0;
}
