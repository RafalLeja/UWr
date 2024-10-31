#include <paro/Object.hpp>

int main(int ac, char* av[])
{
    constexpr auto arr_size = 10u;
    Object** arr = new Object*[arr_size];
    for (int i = 0; i < arr_size; ++i)
        arr[i] = new Object(3*i, 2*i+14, i+92);
    for (int i = 0; i < arr_size; ++i)
        delete arr[i];
    delete[] arr;
    return 0;
}
