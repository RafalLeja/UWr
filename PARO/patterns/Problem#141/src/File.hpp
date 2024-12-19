#pragma once

#include <functional>
#include <string>
#include <fstream>

#include "Logger.hpp"

class File: public Logger
{
public:
    File(std::string f)
    {
        outputFile.open(f);
    }

    void log(std::string s, std::function<std::string(std::string)> func) override
    {
        outputFile << func(s) << std::endl;
    }

    ~File()
    {
        outputFile.close();
    }
private:
    std::ofstream outputFile;
};
