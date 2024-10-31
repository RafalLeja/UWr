#include <iostream>
#include <memory>

struct B;
struct A
{
    std::shared_ptr<B> b;
    ~A() { std::cout << "destructing A\n"; }
};

struct B
{
    std::shared_ptr<A> a;
    ~B() { std::cout << "destructing B\n"; }
};

void useBoth()
{
    auto a = std::make_shared<A>();
    auto b = std::make_shared<B>();
    a->b = b;
    b->a = a;
}

int main()
{
    useBoth();
    std::cout << "Finished using A and B\n";
}
