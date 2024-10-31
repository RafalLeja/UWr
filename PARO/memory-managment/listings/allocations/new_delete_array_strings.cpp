#include <string>

constexpr int arr_size = 40;

int main(int ac, char* av[])
{
    std::string* arr = new std::string[arr_size];
    delete[] arr;

    return 0;
}
