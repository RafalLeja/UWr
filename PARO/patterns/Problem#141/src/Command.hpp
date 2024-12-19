#pragma once
#include <string>
#include <functional>
#include <memory>
#include "Logger.hpp"

class Command
{
public:
    Command(std::shared_ptr<Logger> obj, std::function<std::string(std::string)> met)
    {
        object = obj;
        method = met;
    }

    void execute(std::string s)
    {
        (object->log)(s, method);
    }
private:
    std::shared_ptr<Logger> object;
    std::function<std::string(std::string)> method;
};
