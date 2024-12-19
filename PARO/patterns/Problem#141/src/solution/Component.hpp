#pragma once

#include <string>

class Component
{
public:
    virtual ~Component() = default;

    virtual void execute(std::string s) = 0;
};
