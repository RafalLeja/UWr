#pragma once
#include <iostream>
#include <string>

class Logger
{
public:
    virtual ~Logger() = default;

    virtual void debug(std::string s) = 0;
    virtual void info(std::string s) = 0;
    virtual void error(std::string s) = 0;
};
