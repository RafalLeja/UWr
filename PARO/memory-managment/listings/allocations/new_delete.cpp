#include <paro/Object.hpp>

int main(int ac, char* av[])
{
    Object* p = new Object(3, 14, 92);
    delete p;

    return 0;
}
