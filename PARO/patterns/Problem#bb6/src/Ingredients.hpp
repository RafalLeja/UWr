#pragma once

#include <string>
#include <ostream>
#include <unordered_set>
#include <initializer_list>

struct Ingredients: public std::unordered_set<std::string>
{
    Ingredients() = default;
    Ingredients(std::initializer_list<std::string> i):std::unordered_set<std::string>(i){}

    Ingredients operator-(const Ingredients& other) const
    {
        Ingredients difference;
        for(const auto& elem: *this)
            if(other.find(elem) == other.end())
                difference.insert(elem);
        return difference;
    }

    bool isSubsetOf(const Ingredients& superset) const
    {
        for(const auto& elem: *this)
            if(superset.find(elem) == superset.end())
                return false;
        return true;
    }
};

std::ostream& operator<< (std::ostream& os, Ingredients ingredients)
{
    os << "{";
    for (auto& i: ingredients)
    {
        os << " " << i;
    }
    os << " }";
    return os;
}
