#include <paro/Resource.h>
#include <memory>

int nastyFunction(int param)
{
    if (param % 2)
        throw std::runtime_error("Oops!");
    return 42;
}

void foo(std::shared_ptr<Resource> res, int i) {}

int main(int argc, char const* argv[])
{
    foo(std::shared_ptr<Resource>(new Resource(17)), nastyFunction(17));
    return 0;
}
