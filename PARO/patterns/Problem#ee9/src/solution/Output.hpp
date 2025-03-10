#pragma once
#include <functional>
#include <iostream>
#include <string>

class Output
{
public:
    virtual void write(std::string s, std::function<std::string(std::string)> func) = 0;
};

std::string debug(std::string s)
{
    return "DBG: " + s;
}

std::string info(std::string s)
{
    return "INF: " + s;
}

std::string error(std::string s)
{
    return "ERR: " + s;
}
