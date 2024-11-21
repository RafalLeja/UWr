#pragma once

#include <thread>

struct thread_guard final
{
    explicit thread_guard(std::thread &t)
        : m_t(t)
    {}

    ~thread_guard()
    {
        if (m_t.joinable())
            m_t.join();
    }

private:
    std::thread &m_t;
};
