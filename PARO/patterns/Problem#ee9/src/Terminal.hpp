#pragma once

#include <string>

#include "Logger.hpp"

class Terminal: public Logger
{
public:
    void debug(std::string s) override
    {
        std::cout << "DBG: " << s << std::endl;
    }
    void info(std::string s) override
    {
        std::cout << "INF: " << s << std::endl;
    }
    void error(std::string s) override
    {
        std::cout << "ERR: " << s << std::endl;
    }
};
