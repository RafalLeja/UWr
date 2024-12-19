#pragma once
#include "Status.hpp"
#include <string>
#include <memory>

namespace FSM
{

class Run : public DeviceStatus
{
public:
    Run(ChangeStatusFunction changeStatusFunc,
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
