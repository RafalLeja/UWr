#pragma once

#include <vector>
#include <string>
#include <memory>

#include "Component.hpp"

class Script: public Component
{
public:
    void add(std::unique_ptr<Component> c)
    {
        children.push_back(move(c));
    }

    void execute(std::string s)
    {
        for (auto& child: children)
        {
            child->execute(s);
        }
    }
private:
    std::vector<unique_ptr<Component>> children;
};
