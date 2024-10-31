#include <fstream>
#include <iostream>

int main(int ac, char *av[])
{
    std::fstream file(av[1]);
    std::cout << file.rdbuf();

    return 0;
}
