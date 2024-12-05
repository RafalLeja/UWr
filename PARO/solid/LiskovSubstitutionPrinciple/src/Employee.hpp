#pragma once
#include <iostream>
#include <string>

class Employee
{
public:
    Employee(std::string name, int salary) : name(name), salary(salary)
    {
    }

    virtual ~Employee() = default;

    int getSalary() const
    {
        return salary;
    }

    virtual void raise(int delta)
    {
        salary += delta;
    }

    void sendEmail(std::string message) const
    {
        std::cout << "hello " << name << std::endl << "\t" << message << std::endl;
    }

private:
    std::string name;
    int salary;
};
