#pragma once

#include <string>
#include <map>

enum FuelType {Petrol, Diesel, Lpg};


class Chart;
class Calculator;
class EmailSender;

class FuelPriceDb
{
public:
    FuelPriceDb();
    void initialize(Chart* chart, Calculator* calculator, EmailSender* emailSender);
    void risePrices(float, float, float);
    std::string getPriceOf(FuelType fuel);

private:
    void onChange();

    std::map<FuelType, float> prices;

    Chart* chartHandler;
    Calculator* calculatorHandler;
    EmailSender* emailSenderHandler;
};
