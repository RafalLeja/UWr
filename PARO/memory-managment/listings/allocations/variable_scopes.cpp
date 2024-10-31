#include <print>

struct X
{
    X(int x) : x(x) { std::println("X({}) created", x); }
    ~X() { std::println("X({}) is dead", x); }
    int x;
};

int main(int ac, char* av[])
{
    X a(123);
    {
        X b(42);
    }
    X c(89);

    return 0;
}
