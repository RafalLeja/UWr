#pragma once

#include "BankAccount.hpp"

#include <iostream>
#include <string>

struct Employer
{
    Employer(const std::string& name) : name(name)
    {
    }

    void payWage(unsigned wage, MoneyTransferTarget& account)
    {
        std::cout << name << " pays wage of " << wage << " €" << std::endl;
        account.credit(wage);
    }

private:
    std::string name;
};
