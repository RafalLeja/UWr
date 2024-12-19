#pragma once

#include <functional>
#include <map>

typedef std::function<void ()> Handler;

class Notifier
{
public:
    Notifier()
        :nextAvailableId(0)
    {
    }

    unsigned subscribe(Handler handler)
    {
        handlers[nextAvailableId] = handler;
        return nextAvailableId++;
    }

    void unsubscribe(unsigned id)
    {
        handlers.erase(id);
    }

    void notify()
    {
        for (auto h : handlers)
        {
            h.second();
        }
    }

private:
    std::map<unsigned, Handler> handlers;
    unsigned nextAvailableId;
};

// example of use:
// #include <functional>
// Handler onChangeHandler = std::bind(&Chart::plot, this);
// unsigned subscribeId = notifier->subscribe(onChangeHandler);
