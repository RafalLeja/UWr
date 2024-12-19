#pragma once
#include "Candidate.hpp"

class CandidatesValidator
{
public:
    CandidatesValidator(unsigned cpp, unsigned c, unsigned wage)
        :cppThreshold(cpp), cThreshold(c), wageThreshold(wage)
    {}

    bool shouldBeHired(const Candidate& candidate) const
    {
        if(candidate.cppFluency < cppThreshold)
        {
            return false;
        }
        if(candidate.cFluency < cThreshold)
        {
            return false;
        }
        if(not candidate.cooperative)
        {
            return false;
        }
        if(candidate.preferredWage > wageThreshold)
        {
            return false;
        }
        return true;
    }

private:
    const unsigned cppThreshold;
    const unsigned cThreshold;
    const unsigned wageThreshold;
};
