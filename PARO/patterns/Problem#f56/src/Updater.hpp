#pragma once

class Updater{
public:
    virtual ~Updater() = default;

    virtual void checkForUpdates() = 0;
};
