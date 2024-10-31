#include <memory>

#include <paro/Resource.h>

int main(int ac, char *av[])
{
    std::shared_ptr<Resource> p1(new Resource(17));
    std::shared_ptr<Resource> p2 = p1; // copying is available now!
    std::shared_ptr<Resource> p3 = std::move(p1); // still possible

    use_resource_the_intended_way(*p3);
    return 0;  // p3, p2, p1 went out-of-scope, object is destroyed
}
