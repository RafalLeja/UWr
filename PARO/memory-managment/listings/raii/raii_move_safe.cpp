#include <paro/Data.h>

#include <memory>

std::unique_ptr<Data> create()
{ // RVO
    return std::make_unique<Data>(0x19);
}

void use(std::unique_ptr<Data> p)
{
    if (p) {
        use_data_the_intended_way(p.get());
    }
}

int main(int argc, char const* argv[])
{
    auto data = create();
    use(std::move(data));
    // ...
    use(std::move(data)); // data is NULL!
    return 0;
}
