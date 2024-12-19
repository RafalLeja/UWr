#pragma once
#include "Status.hpp"

namespace FSM
{

class Overheated : public DeviceStatus
{
public:
    Overheated(ChangeStatusFunction changeStatusFunc,
               std::shared_ptr<std::string> taskName)
        :DeviceStatus(changeStatusFunc, taskName)
    {
    }

    void runTask(std::string name) override
    {
        //implement me ...
    }

    void stopTask() override
    {
        //implement me ...
    }

    void coolDown() override
    {
        //implement me ...
    }
};

}
