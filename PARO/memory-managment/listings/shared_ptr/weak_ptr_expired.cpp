#include <iostream>
#include <memory>

void check(std::weak_ptr<int> w)
{
    std::cout << "use_count = " << w.use_count() << '\n';
    // try to upgrade to std::shared_ptr, better than just checking .expired()
    if (auto stillAlive = w.lock()) {
        std::cout << "I am here!\n";
    } else {
        std::cout << "too late...\n";
    }
}

int main(int ac, char *av[])
{
    std::weak_ptr<int> weak;
    {
        auto shared = std::make_shared<int>(17);
        weak = shared;
        check(weak);
    }
    check(weak);
    return 0;
}
