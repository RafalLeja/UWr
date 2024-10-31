#include <filesystem>
#include <print>

struct logger
{
    void set_file(std::filesystem::path p)
    {
        filename = p.filename().c_str();
    }
    const char * filename = nullptr;
};

int main(int ac, char* av[])
{
    std::filesystem::path p = "/path/to/file.txt";
    logger log;
    log.set_file(p);
    std::println("Filename: {}", log.filename);
    return 0;
}
