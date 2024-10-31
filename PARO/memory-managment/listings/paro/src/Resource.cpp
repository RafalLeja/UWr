#include "Resource.h"
#include <print>

Resource acquireResource()
{
    Resource index = 0x17;
    std::println("create Resource({:0x})", index);
    return index;
}

void releaseResource(Resource index)
{
    std::println("remove Resource({:0x})", index);
}

void use_resource_the_intended_way(Resource index) {}
