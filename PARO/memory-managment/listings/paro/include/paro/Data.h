#pragma once

#include <cstdint>
#include <memory>
#include <queue>

struct Data
{
    Data(int id) : id(id) {}
    Data(Data const&) = delete;

    std::uint64_t id;
    std::uint8_t page[4096];
};

inline void use_data_the_intended_way(Data* data) noexcept {}

inline std::queue<int> event_queue;

inline void process(int event) noexcept {}
inline void process(int event, Data& data) noexcept {}

inline std::unique_ptr<Data> load_config() noexcept
{
    return std::make_unique<Data>(0x113);
}

inline void startup(Data const& cfg) noexcept
{
    // perform initial configuration
}

#define EVER   \
    int i = 0; \
    i < 10;    \
    ++i
