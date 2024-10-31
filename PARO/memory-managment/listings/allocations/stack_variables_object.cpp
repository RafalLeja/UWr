#include <paro/Object.hpp>

int proc(int a, int b, int c)
{
    Object o(a, b, c);

    return o.method();
}

int main(int ac, char* av[])
{
    int p = proc(11, 13, 16);

    return 0;
}
