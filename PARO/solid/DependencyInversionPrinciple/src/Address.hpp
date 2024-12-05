#pragma once

#include <ostream>
#include <string>

class Address
{
public:
    Address(const std::string& path) : path(path)
    {
    }

    friend std::ostream& operator<<(std::ostream& os, const Address& address)
    {
        return os << address.path;
    }

private:
    std::string path;
};
