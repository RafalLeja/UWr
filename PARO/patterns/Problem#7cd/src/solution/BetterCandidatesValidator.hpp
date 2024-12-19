#pragma once
#include <memory>

class Candidate;

class BetterCandidatesValidator
{
public:
    virtual ~BetterCandidatesValidator() = default;

    void add(std::unique_ptr<BetterCandidatesValidator> c)
    {
        if (next)
            next->add(move(c));
        else
            next = move(c);
    }

    bool shouldBeHired(const Candidate& c) const
    {
        if(next)
             return validate(c) and next->shouldBeHired(c);
        return validate(c);
    }

protected:
    virtual bool validate(const Candidate& c) const = 0;

private:
    std::unique_ptr<BetterCandidatesValidator> next;
};
