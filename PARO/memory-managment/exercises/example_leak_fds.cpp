#include <cstdio>
#include <filesystem>
#include <memory>
#include <string>

struct Logger
{
    explicit Logger(std::filesystem::path path)
        : logfile(std::fopen(path.c_str(), "wb"))
    {
        std::fputs("Starting logger...\n", logfile);
    }

    Logger(const Logger& other) = delete;
    Logger& operator=(const Logger& other) = delete;

    void log(std::string text) const noexcept
    {
        std::string line = "LOG: " + std::move(text) + "\n";
        std::fputs(line.c_str(), logfile);
    }

private:
    std::FILE* logfile;
};

std::shared_ptr<Logger> create_logger()
{
    return std::make_shared<Logger>("log.txt");
}

struct Service
{
    Service(std::string name, std::shared_ptr<Logger> logger)
        : text_(name + " is working"),
          logger_(std::move(logger))
    {
        logger_->log("Service " + std::move(name) + " is created");
    }

    void doStuff() const { logger_->log(text_); }

private:
    std::string text_;
    std::shared_ptr<Logger> logger_;
};

int main(int ac, char* av[])
{
    auto logger = create_logger();
    auto serviceA = Service("A", logger);
    auto serviceB = Service("B", logger);
    auto serviceC = Service("C", logger);

    for (const auto s : {&serviceA, &serviceB, &serviceC}) { s->doStuff(); }
}
