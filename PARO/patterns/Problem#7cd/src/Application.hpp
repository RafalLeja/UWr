#pragma once

#include "Candidate.hpp"
#include "BetterCandidatesValidator.hpp"

#include <algorithm>
#include <vector>

std::vector<Candidate> getFilteredCandidates(
    const std::vector<Candidate>& candidates,
    const BetterCandidatesValidator& requirements)
{
    std::vector<Candidate> qualified;
    std::copy_if(
        candidates.begin(), candidates.end(), std::back_inserter(qualified),
        [&](Candidate c) { return requirements.shouldBeHired(c); });
    return qualified;
}
