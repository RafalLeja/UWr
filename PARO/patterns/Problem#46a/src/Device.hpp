#pragma once
#include <string>
#include <memory>
#include <iostream>

class Device
{
public:
    Device()
    {
    }

    void runTask(std::string name)
    {
        if(isRunning)
        {
            std::cout << "Can't run: " << name << " , because " << taskName << " is running now. Device is overheated!\n";
            isOverheated = true;
            isRunning = false;
            return;
        }
        if(isOverheated)
        {
            std::cout << "Can't run: " << name << " , because device is overheated\n";
            return;
        }

        taskName = name;
        isRunning = true;
        std::cout << "Started task: " << taskName << "\n";

    }

    void stopTask()
    {
        if(isRunning)
        {
            std::cout << taskName << " stopped!\n";
            isRunning = false;
            return;
        }
        if(isOverheated)
        {
            std::cout << "No task to stop. Device is overheated\n";
            return;
        }
        std::cout << "No task to stop.\n";
    }

    void coolDown()
    {
        if(isOverheated)
        {
            std::cout << "Cooling down\n";
        }
        else
        {
            std::cout << "Nothing to cool down\n";
        }
        isOverheated = false;

    }

private:
    std::string taskName;
    bool isRunning = false;
    bool isOverheated = false;
};

