#pragma once

#include "BetterCandidatesValidator.hpp"
#include "../Candidate.hpp"

class CppRequirements: public BetterCandidatesValidator
{
public:
    CppRequirements(unsigned cpp){
        minCppRequirements = cpp;
    }

    bool validate(const Candidate& c) const override
    {
        return minCppRequirements <= c.cppFluency;
    }
private:
    unsigned minCppRequirements;
};
