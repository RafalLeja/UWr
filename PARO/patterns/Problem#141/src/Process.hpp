#pragma once
#include "Command.hpp"

class Process
{
public:
    Process(std::unique_ptr<Command> dbg, std::unique_ptr<Command> inf, std::unique_ptr<Command> err):
        debug(std::move(dbg)), info(std::move(inf)), error(std::move(err))
    {}

    void startup()
    {
        info->execute("process started");
    }

    void doStuff()
    {
        debug->execute("just about to do stuff");
        debug->execute("something is wrong");

        error->execute("dividing by zero. Autodestruction in 3...");
    }
private:
    std::unique_ptr<Command> debug, info, error;
};
