#pragma once

#include "Address.hpp"
#include "SqlStorage.hpp"

#include <sstream>
#include <string>

class EventLog
{
public:
    EventLog(Storage& strg) : storage(strg)
    {
    }

    void log(const std::string& message)
    {
        std::stringstream buffer;
        buffer << "[" << (logsStored++) << "] " << message;
        storage.append(buffer.str());
    }

private:
    Storage& storage;
    unsigned logsStored = 0;
};
