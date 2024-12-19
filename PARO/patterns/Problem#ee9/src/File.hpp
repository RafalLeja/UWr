#pragma once

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

    void debug(std::string s) override
    {
        outputFile << "DBG: " << s << std::endl;
    }
    void info(std::string s) override
    {
        outputFile << "INF: " << s << std::endl;
    }
    void error(std::string s) override
    {
        outputFile << "ERR: " << s << std::endl;
    }

    ~File()
    {
        outputFile.close();
    }
private:
    std::ofstream outputFile;
};
