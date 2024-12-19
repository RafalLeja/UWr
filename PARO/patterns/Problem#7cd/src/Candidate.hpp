#pragma once
#include <stdexcept>
#include <cmath>
#include <string>

class Candidate
{
public:
    Candidate(std::string name, unsigned cpp, unsigned c, bool coop, unsigned wage):
        name(name), cppFluency(cpp), cFluency(c), cooperative(coop), preferredWage(wage)
    {
        if (cpp > 100 || c > 100)
            throw std::overflow_error("you can't be more than 100% fluent");
    }

    std::string name;
    unsigned cppFluency;
    unsigned cFluency;
    bool cooperative;
    unsigned preferredWage;
};
