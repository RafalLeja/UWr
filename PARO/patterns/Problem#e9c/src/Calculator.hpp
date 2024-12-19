#pragma once
#include <iostream>

#include <FuelPriceDb.hpp>
#include <DbClient.hpp>

class Calculator : public DbClient
{
public:
    Calculator(FuelPriceDb& db)
        :DbClient(db)
    {
    }

    void recalculate()
    {
        std::cout << "Calculator::recalculate()  new price of diesel " << database.getPriceOf(Diesel) << "\n";
    }
};
