#pragma once

#include "BetterCandidatesValidator.hpp"
#include "../Candidate.hpp"

class WageRequirements: public BetterCandidatesValidator
{
public:
    WageRequirements(unsigned w) {
        maxPreferredWage = w;
    }

    bool validate(const Candidate& c) const override
    {
        return maxPreferredWage >= c.preferredWage;
    }
private:
    unsigned maxPreferredWage;
};
