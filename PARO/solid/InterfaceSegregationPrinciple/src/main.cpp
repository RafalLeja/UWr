#include "BankAccount.hpp"
#include "Person.hpp"
#include "Employer.hpp"
#include "Shop.hpp"

#include <iostream>

int main()
{
    BankAccount bobsAccount;
    Person bob{"Bob", bobsAccount};

    Employer bobsEmployer{"George's Garage"};
    bobsEmployer.payWage(2500, bobsAccount);
    bob.lookIntoAccount();

    Shop localGrocery{"Alice's Grocery"};
    localGrocery.buyApples(bobsAccount);
    bob.lookIntoAccount();

    bob.lookIntoAccount();
    return 0;
}
