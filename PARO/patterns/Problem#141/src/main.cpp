#include <memory>
#include "Command.hpp"
#include "Terminal.hpp"
#include "File.hpp"
#include "Process.hpp"

int main()
{
    auto terminal = std::make_shared<Terminal>();
    auto file = std::make_shared<File>("filename.txt");
    auto dbg = std::make_unique<Command>(std::move(terminal), debug);
    auto inf = std::make_unique<Command>(file, info);
    auto err = std::make_unique<Command>(file, error);

    Process p(std::move(dbg), std::move(inf), std::move(err));
    p.startup();
    p.doStuff();
}
