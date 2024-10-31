#include <cstdio> // fopen/fclose
#include <memory>

struct Deleter
{
    void operator()(std::FILE* file) const noexcept { std::fclose(file); }
};
void process_file(std::FILE* file);

int main(int ac, char* av[])
{
    constexpr auto path = "/path/to/file.txt";
    std::unique_ptr<std::FILE, Deleter> file(std::fopen(path, "r"));
    if (file) {
        process_file(file.get()); // may throw!
    }
    return 0;
}

void process_file(std::FILE* file)
{
    // process file
}
