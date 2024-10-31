#include <memory>
#include <vector>

struct Data
{
    char tab_[42];
};

int main(int ac, char *av[])
{
    constexpr unsigned size = 10'000'000u;
    std::vector<Data*> vec;
    vec.reserve(size);
    for (auto i = 0u; i < size; i++) {
        auto p = new Data();
        vec.push_back(std::move(p));
    }
    for (auto p : vec) delete p;
}
