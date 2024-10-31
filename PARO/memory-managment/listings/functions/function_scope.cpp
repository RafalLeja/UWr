#include <print>

void ptr(int* ptr)
{
    if (ptr) {
        std::println("{}", *ptr);
        delete ptr;
    }
    ptr = nullptr;
}

int main(int ac, char* av[])
{
    int* p = new int(45);
    ptr(p);
    std::println("Is nullptr? {}.", p == nullptr);

    return 0;
}
