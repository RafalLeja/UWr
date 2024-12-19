#pragma once
#include <string>
#include <memory>
#include <map>
#include "Status.hpp"
#include "Off.hpp"
#include "Run.hpp"
#include "Overheated.hpp"

namespace FSM
{

class Device
{
public:
    Device()
    {
        createStatusesMap();
        currentStatus = allStatuses[OFF];
    }

    void runTask(std::string name)
    {
        currentStatus->runTask(name);
    }

    void stopTask()
    {
        currentStatus->stopTask();
    }

    void coolDown()
    {
        currentStatus->coolDown();
    }

private:
    void createStatusesMap()
    {
        ChangeStatusFunction transition = [this](Status status)
        {
            std::cout << "Changing status to: " << status << std::endl;
            this->currentStatus = allStatuses[status];
        };

        auto taskName = std::make_shared<std::string>();

        allStatuses[OFF] = std::make_shared<Off>(transition, taskName);
        allStatuses[RUN] = std::make_shared<Run>(transition, taskName);
        allStatuses[OVERHEATED] = std::make_shared<Overheated>(transition, taskName);
    }

    std::map<Status, std::shared_ptr<DeviceStatus>> allStatuses;
    std::shared_ptr<DeviceStatus> currentStatus;
};

}
