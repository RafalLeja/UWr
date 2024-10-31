#include <fstream>
#include <mutex>

struct GameData
{
    GameData() : save("save.dat"), player_level(1) {}

    std::fstream save;
    std::mutex the_mutex;
    int player_level;
};

int main(int argc, char* argv[])
{
    // resources are acquired during initialization
    GameData data;

    return 0;
}
