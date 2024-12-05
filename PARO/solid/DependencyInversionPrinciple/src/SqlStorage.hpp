#pragma once

#include "Address.hpp"

#include <iostream>
#include <string>

class SqlStorage
{
public:
    SqlStorage(const Address& address) : address(address)
    {
        std::cout << "Established connection to SQL server at " << address << std::endl;
    }

    void append(const std::string& entry)
    {
        std::cout << "SQL@" << address << " <- " << entry << std::endl;
    }

private:
    Address address;
};
