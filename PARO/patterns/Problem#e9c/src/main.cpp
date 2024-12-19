#include <FuelPriceDb.hpp>
#include <EmailSender.hpp>
#include <Calculator.hpp>
#include <Chart.hpp>


int main()
{
    FuelPriceDb database;

    Chart chart(database);
    Calculator calculator(database);

    {
        EmailSender emailSender(database);
        database.initialize(&chart, &calculator, &emailSender);
        database.risePrices(5.55, 5.45, 1.90);
    }

    database.risePrices(0.45, 0.55, 1.60);
}
