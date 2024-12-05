#pragma once

#include "BankAccount.hpp"

#include <iostream>
#include <string>

struct Shop
{
    Shop(const std::string& name) : shopName(name)
    {
    }

    void buyApples(BankAccount& account)
    {
        const unsigned price = 1999;
        std::cout << shopName << " sells an apple for " << price << " €" << std::endl;
        account.debit(price);
    }

private:
    std::string shopName;
};
