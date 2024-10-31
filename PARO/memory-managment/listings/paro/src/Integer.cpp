#include "Integer.hpp"

#include <print>

Integer::Integer(char name) : name(name)
{
    std::println("create Integer({})", name);
}

Integer::~Integer()
{
    std::println("delete Integer({})", name);
}
