#pragma once

#include "CommandHandler.hpp"
#include <iostream>

struct Quitter : CommandHandler
{
public:
    std::string getCommandName() const override
    {
        return "quit";
    }

    void handle(const std::vector<std::string>& parameters) const override
    {
        std::cout << "Console terminates now!" << std::endl;
        exit(0);
    }
};

struct Printer : CommandHandler
{
public:
    std::string getCommandName() const override
    {
        return "print";
    }

    void handle(const std::vector<std::string>& parameters) const override
    {
        for (const auto& p : parameters)
            std::cout << p << " ";
        std::cout << std::endl;
    }
};
