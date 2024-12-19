#include <memory>
#include "Logger.hpp"
#include "File.hpp"
#include "Terminal.hpp"
#include "Process.hpp"

int main()
{
    auto term = std::unique_ptr<Logger>(new Terminal());
    auto file = std::unique_ptr<Logger>(new File("filename.txt"));

    Process p(std::move(term), std::move(file));
    p.startup();
}
