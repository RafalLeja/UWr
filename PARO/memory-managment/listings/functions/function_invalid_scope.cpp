#include <print>

struct S
{
    S(char n) : n(n) { std::println("S('{}') created.", n); }
    ~S() { std::println("S('{}') destroyed", n); }

    char n;
};

char& get_initial(S s) { return s.n; }

int main(int ac, char* av[])
{
    auto& s = get_initial(S{'B'});
    std::println("In main again: {}", s);
    return 0;
}
