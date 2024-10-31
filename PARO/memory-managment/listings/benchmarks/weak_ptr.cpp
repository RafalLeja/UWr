#include <memory>
#include <vector>

struct Data
{
    char tab_[42];
};

int main(int ac, char *av[])
{
    constexpr unsigned size = 10'000'000u;
    std::vector<std::shared_ptr<Data>> vec;
    std::vector<std::weak_ptr<Data>> vec_observers;
    vec.reserve(size);
    vec_observers.reserve(size);
    for (auto i = 0u; i < size; i++) {
        std::shared_ptr<Data> p{new Data()};
        std::weak_ptr<Data> weak{p};
        vec.push_back(std::move(p));
        vec_observers.push_back(std::move(weak));
    }
}
