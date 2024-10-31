#include <memory>
#include <paro/Resource.h>

struct Deleter // std::default_delete<Resource>
{
    void operator()(Resource* p) const noexcept
    {
        delete p;
    }
};

int main(int ac, char* av[])
{
    std::unique_ptr<Resource, Deleter> res(new Resource(17));
    if (res) {
        use_resource_the_intended_way(*res);
    }
    return 0;
}
