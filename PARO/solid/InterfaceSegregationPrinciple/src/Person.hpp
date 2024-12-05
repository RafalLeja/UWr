#pragma once

#include "BankAccount.hpp"

#include <iostream>
#include <string>
#include <vector>

struct Person
{
    Person(const std::string& name, BankAccount& account) : name(name), account(account)
    {
    }

    void lookIntoAccount() const
    {
        std::cout << name << " looks into account and finds " << account.balance() << " € there" << std::endl;
        account.credit(20);
    }

private:
    std::string name;
    BankAccount& account;
};
