#pragma once
#include "Employee.hpp"

class SummerTrainee : public Employee
{
public:
    SummerTrainee(std::string name) : Employee(name, 0)
    {
    }

    void raise(int) override
    {
    }
};
