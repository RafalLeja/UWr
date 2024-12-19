#pragma once
#include <iostream>
#include <chrono>
#include <thread>
#include <string>

#include "Updater.hpp"

class GreeterUpdater: public Updater{
public:
    GreeterUpdater(){
        for(unsigned int i = 1; i < 4; i = (i + 1) % 4){
            std::cout << "\033c";
            std::cout << "connecting to the database" << std::string(i, '.') << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    void checkForUpdates(){
        std::cout << "checking for updates" << std::endl;
    }
};
