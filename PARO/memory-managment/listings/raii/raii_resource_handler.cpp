#include <paro/Resource.h>

class ResourceHandler
{
public:
    ResourceHandler() : resource(acquireResource()) {}
    ~ResourceHandler() { releaseResource(resource); }

    // copy forbidden!
    ResourceHandler(ResourceHandler const&) = delete;
    ResourceHandler& operator=(ResourceHandler const&) = delete;

    ResourceHandler(ResourceHandler&&) noexcept;
    ResourceHandler& operator=(ResourceHandler&&) noexcept;

private:
    Resource resource;
};

#include <utility>

ResourceHandler::ResourceHandler(ResourceHandler&& other) noexcept
    : resource(std::exchange(other.resource, 0x0))
{}

ResourceHandler& ResourceHandler::operator=(ResourceHandler&& other) noexcept
{
    resource = other.resource;
    other.resource = 0x0; // clear!
    return *this;
}

int main(int argc, char const* argv[])
{
    ResourceHandler rh;

    return 0;
}
