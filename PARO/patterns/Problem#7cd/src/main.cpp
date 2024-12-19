#include <vector>
#include <iostream>

#include "Application.hpp"
#include "Candidate.hpp"

#include "CooperationNeeded.hpp"
#include "CppRequirements.hpp"
#include "CRequirements.hpp"
#include "WageRequirements.hpp"

int main()
{
    std::vector<Candidate> candidates{
        {"Adelajda", 15, 87, 0, 12000},
        {"Brunhilda", 85, 42, 1, 11000},
        {"Ciechosław", 97, 92, 1, 25000},
        {"Domażyr", 91, 45, 0, 10000}};

    // CandidatesValidator requirements(20, 0, 15000);

    std::unique_ptr<BetterCandidatesValidator> coop = std::make_unique< CooperationNeeded>(true);
    std::unique_ptr<BetterCandidatesValidator> cpp = std::make_unique< CppRequirements>(20);
    std::unique_ptr<BetterCandidatesValidator> c = std::make_unique< CRequirements>(0);
    std::unique_ptr<BetterCandidatesValidator> wage = std::make_unique< WageRequirements>(15000);

    coop->add(std::move(cpp));
    coop->add(std::move(c));
    coop->add(std::move(wage));

    for (auto candidate: getFilteredCandidates(candidates, *coop))
    {
        std::cout << "candidate " << candidate.name << " seems to fit" << std::endl;
    }
}
