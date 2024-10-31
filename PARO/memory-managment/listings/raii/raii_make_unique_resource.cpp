#include <memory>
#include <paro/Resource.h>

int main(int ac, char* av[])
{
    auto res = std::make_unique<Resource>(17);
    if (res) {
        use_resource_the_intended_way(*res);
    }
    return 0;
}
