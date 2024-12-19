#pragma once

#include "BetterCandidatesValidator.hpp"
#include "../Candidate.hpp"

class CRequirements: public BetterCandidatesValidator
{
public:
    CRequirements(unsigned c) {
        minCRequirements = c;
    }

    bool validate(const Candidate& c) const override
    {
        return minCRequirements <= c.cFluency;
    }
private:
    unsigned minCRequirements;
};
