#include <paro/File.h>

int main(int ac, char *av[])
{
    auto file = std::fopen(av[1], "r");
    print_file(file);

    return 0;
}
