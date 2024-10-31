#include <print>

struct X
{
    X(int x) : x(x) { std::println("X({}) created", x); }
    ~X() { std::println("X({}) is dead", x); }
    int x;
};

int main(int ac, char* av[])
{
    X* a = nullptr;
    {
        X b(42);
        a = &b; // save for later
    }
    a->x = 8; // whoops!

    return 0;
}
