#pragma once
#include <iostream>

#include <FuelPriceDb.hpp>
#include <DbClient.hpp>

class Chart : public DbClient
{
public:
    Chart(FuelPriceDb& db)
        :DbClient(db)
    {
    }

    void plot()
    {
        std::cout << "Chart::plot()              new price of petrol " << database.getPriceOf(Petrol) << "\n";
    }
};
