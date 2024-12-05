#pragma once

#include <iostream>
#include <string>

#include "Debitable.hpp"
#include "OwnedAccount.hpp"
#include "MoneyTransferTarget.hpp"

class BankAccount : public Debitable, public OwnedAccount, public MoneyTransferTarget
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
