#pragma once

#include <memory>

template <class Mock> struct UniqueMock
{
    UniqueMock() : mock(std::make_unique<Mock>()), ptr(mock.get()) {}

    Mock& operator*() const noexcept { return *ptr; }

    std::unique_ptr<Mock> obtain()
    {
        if (not mock) {
            throw std::runtime_error("Mock already moved.");
        }
        return std::move(mock);
    }

private:
    std::unique_ptr<Mock> mock{ptr};
    Mock* ptr;
};
