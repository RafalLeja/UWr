#include <iostream>

int main(int ac, char* argv[])
{
    int* leak = new int(14);

    std::cout << "[" << leak << "] => " << *leak << std::endl;

    delete leak;
    return 0;
}
