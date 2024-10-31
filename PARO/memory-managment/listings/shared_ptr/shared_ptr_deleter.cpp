#include <memory>
#include <vector>

#include <paro/Resource.h>

int main(int ac, char* av[])
{
    auto deleterOdd = [](Resource* r) { delete r; }; // custom deleter
    auto deleterEven = [](Resource* r) { delete r; }; // different types

    std::shared_ptr<Resource> p1(new Resource(13), deleterOdd);
    std::shared_ptr<Resource> p2(new Resource(26), deleterEven);
    // impossible with std::unique_ptr!
    std::vector<std::shared_ptr<Resource>> vec{p1, p2};
    return 0;
}
