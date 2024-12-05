#pragma once

#include "Address.hpp"
#include "SqlStorage.hpp"

#include <sstream>
#include <string>

class EventLog
{
public:
    EventLog(const Address& sqlServerAdress) : storage(sqlServerAdress)
    {
    }

    void log(const std::string& message)
    {
        std::stringstream buffer;
        buffer << "[" << (logsStored++) << "] " << message;
        storage.append(buffer.str());
    }

private:
    SqlStorage storage;
    unsigned logsStored = 0;
};
