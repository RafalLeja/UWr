#include <paro/File.h>

int main(int ac, char *av[])
{
    auto file = std::fopen(av[1], "r");
    if (not file)
        return 1;
    try {
        print_file(file);
    } catch (...) {
        std::fclose(file);  // again?
        return 2;
    }
    return 0;
}
