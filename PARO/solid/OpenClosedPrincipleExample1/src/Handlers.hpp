#pragma once

#include <iostream>
#include <string>

namespace Functions
{

void print(const std::vector<std::string>& strings)
{
    for (const auto& s : strings)
        std::cout << s << " ";
    std::cout << std::endl;
}

static void quit()
{
    std::cout << "Console terminates now!" << std::endl;
    exit(0);
}

}
