// TODO: Prepare example and explanation for shared_ptr aliasing constructor

#include <memory>
#include <functional>

struct Plugin {};

void use_plugin(Plugin&) {};

std::shared_ptr<std::function<void()>> load_plugin()
{
    auto x = std::make_shared<Plugin>(); // standard deleter
    std::function<void()> func = [x] {
        use_plugin(*x);
    };

    return std::shared_ptr<std::function<void()>>(x, *func);
}

int main(int ac, char* av[])
{
    auto plugin = load_plugin();
    (*plugin)(); // shared_ptr holds function
    return 0; // plugin destroyed
}
