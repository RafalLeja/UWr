#include <memory>

#include <paro/Resource.h>

int main(int ac, char *av[])
{
    std::unique_ptr<Resource> p1(new Resource(17));
    // std::unique_ptr<Resource> p2 = p1; // non-copyable!
    std::unique_ptr<Resource> p3 = std::move(p1);

    use_resource_the_intended_way(*p3);

    p3.reset(); // delete resource
    p1.reset(); // does nothing
    return 0;
}
