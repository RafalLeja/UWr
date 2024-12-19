#pragma once

#include <string>
#include <functional>

#include "Logger.hpp"

class Terminal: public Logger
{
public:
    void log(std::string s, std::function<std::string(std::string)> func) override
    {
        std::cout << func(s) << std::endl;
    }
};
