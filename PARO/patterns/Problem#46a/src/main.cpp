#include "Device.hpp"

int main()
{
    Device device;
    device.runTask("first task");
    device.runTask("second task");
    device.coolDown();
    device.coolDown();
    device.runTask("third task");
    device.stopTask();
}
