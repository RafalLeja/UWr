#pragma once
#include <string>
#include <functional>
#include <iostream>
#include <memory>

namespace FSM
{

enum Status
{
    OFF = 1,
    RUN = 2,
    OVERHEATED = 3
};


typedef std::function<void (Status)> ChangeStatusFunction;

class DeviceStatus
{
public:
    DeviceStatus(ChangeStatusFunction changeStatus,
                std::shared_ptr<std::string> taskName)
        : changeStatusFunc(changeStatus),
          taskName(taskName)
    {}

    virtual void runTask(std::string name) = 0;
    virtual void stopTask() = 0;
    virtual void coolDown() = 0;

    virtual ~DeviceStatus() {}

private:
   ChangeStatusFunction changeStatusFunc;

protected:
    void changeStatusTo(Status newStatus)
    {
        std::cout << "DEBUGLOG: changing status to:" << newStatus << "\n";
        changeStatusFunc(newStatus);
    }
    std::shared_ptr<std::string> taskName;
};

}

