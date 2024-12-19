#pragma once
#include <string>
#include <functional>
#include <memory>
#include "Output.hpp"


typedef std::function<std::string(std::string)> Method;

class BetterLogger
{
public:
    BetterLogger(std::shared_ptr<Output> output, Method method)
        :output(output), method(method)
    {
    }

    void log(std::string s)
    {
        (output->write)(s, method);
    }
private:
    std::shared_ptr<Output> output;
    Method method;
};
