#pragma once
#include "Status.hpp"

namespace FSM
{

class Off : public DeviceStatus
{
public:
    Off(ChangeStatusFunction changeStatusFunc,
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
