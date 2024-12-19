#pragma once

#include "BetterCandidatesValidator.hpp"
#include "../Candidate.hpp"

class CooperationNeeded: public BetterCandidatesValidator
{
public:
    CooperationNeeded(bool q){
        querry = q;
    }

    bool validate(const Candidate& c) const override
    {
        return c.cooperative == querry;
    }

private:
    bool querry;
};
