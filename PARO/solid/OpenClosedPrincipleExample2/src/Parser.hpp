#pragma once

#include "Data.hpp"

#include <iterator>
#include <sstream>
#include <string>
#include <vector>

class Parser
{
public:
    Data parse(const std::string& line)
    {
        if (line.empty()) return {};

        std::stringstream ss{line};
        return {readCommand(ss), readParameters(ss)};
    }

private:
    std::string readCommand(std::stringstream& ss) const
    {
        std::string result;
        ss >> result;
        return result;
    }
    std::vector<std::string> readParameters(std::stringstream& ss) const
    {
        return std::vector<std::string>(std::istream_iterator<std::string>(ss), std::istream_iterator<std::string>());
    }
};
