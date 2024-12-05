#pragma once

#include <iostream>
#include <string>

class BankAccount
{
public:
    bool debit(unsigned amount)
    {
        if (amount > currentBalance)
        {
            return false;
        }

        currentBalance -= amount;
        return true;
    }

    void credit(unsigned deposit)
    {
        currentBalance += deposit;
    }

    int balance() const
    {
        return currentBalance;
    }

private:
    int currentBalance = 0;
};
