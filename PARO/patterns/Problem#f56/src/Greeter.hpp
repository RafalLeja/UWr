#pragma once

#include <iostream>
#include <memory>

#include "Updater.hpp"

class Greeter{
public:
    Greeter(std::unique_ptr<Updater> up): updater(std::move(up))
    {}

    void greet()
    {
        char choice = 'a';
        while (choice != 'e'){
            std::cout << "r- run\nu- check for updates\ne- exit" << std::endl;
            std::cin >> choice; std::cin.ignore();
            switch (choice){
            case 'r':
                std::cout << "hello world" << std::endl;
                break;
            case 'u':
                updater->checkForUpdates();
                break;
            }
        }
    }
private:
    std::unique_ptr<Updater> updater;
};
