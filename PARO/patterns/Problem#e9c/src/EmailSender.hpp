#pragma once
#include <iostream>

#include <FuelPriceDb.hpp>
#include <DbClient.hpp>

class EmailSender : public DbClient
{
public:
    EmailSender(FuelPriceDb& db)
        :DbClient(db)
    {
    }

    void send()
    {
        std::cout << "EmailSender::send()        new price of lpg    " << database.getPriceOf(Lpg) << "\n";
    }
};
