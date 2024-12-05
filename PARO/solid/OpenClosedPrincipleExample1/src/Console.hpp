#pragma once

#include "Data.hpp"
#include "Handlers.hpp"
#include "Parser.hpp"

#include <iostream>


class Console
{
public:
    void run()
    {
        std::cout << "Welcome in terminal simulator.\nTry commands: \nprint [args...] \nquit" << std::endl;
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
        if (data.command == "quit")
            Functions::quit();
        else if (data.command == "print")
            Functions::print(data.parameters);
        else
            return false;
        return true;
    }

    Parser parser;
};
