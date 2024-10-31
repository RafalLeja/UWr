#include "Heap.hpp"

#define FMT_HEADER_ONLY
#include <fmt/format.h>

void Heap::print_allocated() const noexcept
{
    fmt::print("Heap allocations: ");
    for (auto const& block : this->mp) {
        fmt::print("[{}B:({}-{})]",
                   block.second,
                   block.first,
                   block.first + block.second - 1);
    }
    fmt::print("\n");
}

void Heap::print_free() const noexcept
{
    fmt::print("Heap availability: ");
    for (int i = 0; i < free_list.size(); ++i) {
        fmt::print("[{:d}B:", 1 << i);
        for (auto const& block : free_list.at(i))
            fmt::print("({}-{})", block.first, block.second);
        fmt::print("]");
    }
    fmt::print("\n");
}

void Heap::print_memory() const noexcept
{
    constexpr int width = 16; // line width
    constexpr int word = 4; // word marker

    fmt::print("     ");
    for (int i = 0; i < width; ++i) {
        if (!(i % word)) {
            fmt::print("{:2x} ", i);
        } else {
            fmt::print("   ");
        }
    }

    for (int i = 0; i < _sz; ++i) {
        if (!(i % width)) {
            fmt::print("\n{:#04x}:", i);
        }
        fmt::print("{:2x} ", static_cast<std::uint8_t>(((char*)_memory)[i]));
    }
    fmt::print("\n");
}
