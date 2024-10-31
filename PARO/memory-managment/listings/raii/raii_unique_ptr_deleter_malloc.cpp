#include <cstdlib> // malloc/free
#include <memory>

struct Deleter
{
    void operator()(char* p) const noexcept { std::free(p); }
};
void perform_task(char* buffer, std::size_t buf_size);

int main(int ac, char* av[])
{
    constexpr std::size_t buf_size = 1024;
    std::unique_ptr<char, Deleter> buffer((char*)std::malloc(buf_size));
    if (buffer) {
        perform_task(buffer.get(), buf_size); // may throw!
    }
    return 0;
}

void perform_task(char* buffer, std::size_t buf_size)
{
    // performing some task with buffer
}
