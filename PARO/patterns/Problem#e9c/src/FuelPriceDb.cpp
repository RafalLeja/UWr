#include <sstream>
#include <iomanip>

#include <FuelPriceDb.hpp>
#include <EmailSender.hpp>
#include <Calculator.hpp>
#include <Chart.hpp>


FuelPriceDb::FuelPriceDb()
{
    prices[Petrol] = 0;
    prices[Diesel] = 0;
    prices[Lpg] = 0;
}

void FuelPriceDb::initialize(Chart* chart, Calculator* calculator, EmailSender* emailSender)
{
    chartHandler = chart;
    calculatorHandler = calculator;
    emailSenderHandler = emailSender;
}

void FuelPriceDb::risePrices(float deltaPetrolPrice, float deltaDieselPrice, float deltaAutogasPrice)
{
    prices[Petrol] += deltaPetrolPrice;
    prices[Diesel] += deltaDieselPrice;
    prices[Lpg] += deltaAutogasPrice;
    onChange();
}

void FuelPriceDb::onChange()
{
  chartHandler->plot();
  calculatorHandler->recalculate();
  emailSenderHandler->send();
}

std::string FuelPriceDb::getPriceOf(FuelType fuel)
{
    std::stringstream stream;
    stream << "today is: " << std::fixed << std::setprecision(2) << prices[fuel];
    return stream.str();
}
