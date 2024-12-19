#pragma once
#include <FuelPriceDb.hpp>

class DbClient
{
public:
    DbClient(FuelPriceDb& db)
        :database(db)
    {
    }

    virtual ~DbClient()
    {
    }

protected:
    FuelPriceDb& database;
};
