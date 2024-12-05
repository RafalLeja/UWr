#pragma once

#include "CommandHandler.hpp"
#include "Data.hpp"
#include "Parser.hpp"

#include <iostream>
#include <memory>
#include <vector>


class Console
{
public:
    void addHandler(std::unique_ptr<CommandHandler> handler)
    {
        handlers.push_back(std::move(handler));
    }

    void run()
    {
        std::cout << "Welcome in terminal simulator.\nTry commands:\n";
        for (const auto& handler : handlers)
        {
            std::cout << handler->getCommandName() << "\n";
        }
        while (true)
        {
            std::cout << ">";
            std::string line;
            getline(std::cin, line);
            const auto data = parser.parse(line);
            if (not handle(data))
                std::cout << "*** Unknown command! ***" << std::endl;
        }
    }

private:
    bool handle(const Data& data)
    {
        for (const auto& handler : handlers)
        {
            if (handler->getCommandName() == data.command)
            {
                handler->handle(data.parameters);
                return true;
            }
        }
        return false;
    }

    Parser parser;
    std::vector<std::unique_ptr<CommandHandler>> handlers;
};
