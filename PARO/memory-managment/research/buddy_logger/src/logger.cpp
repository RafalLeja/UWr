#include "logger.hpp"

#define FMT_HEADER_ONLY
#include <fmt/format.h>

namespace logger
{
void log_out_of_memory_max_size_exceeded(int requested_size,
                                         std::size_t max_size)
{
    // there is no block greater than 2 to the power of free_list size
    fmt::print("Allocate request for {} bytes failed - out of memory! "
               "Max block size: {}B\n",
               requested_size,
               (1 << max_size));
}

void log_out_of_memory_block_truncated(int requested_size,
                                       int truncated_block_size)
{
    // block is truncated when heap size is not exactly the power of 2
    fmt::print("Allocate request for {} bytes failed - out of memory! "
               "Last block truncated to {} bytes.\n",
               requested_size,
               truncated_block_size);
}

void log_allocation_success(int requested_size,
                            std::pair<int, int> const& block)
{
    auto block_size = block.second - block.first + 1;
    fmt::print("Allocate request for {} bytes succeed - memory block ({}-{}) "
               "allocated.\n",
               requested_size,
               block.first,
               block.second);
    if (block_size > requested_size) {
        fmt::print("Note: {} bytes wasted due to block alignment.\n",
                   block_size - requested_size);
    }
    fmt::print("\n");
}

void log_out_of_memory(int requested_size)
{
    fmt::print("Sorry, failed to allocate memory."
               " Block suitable for {} bytes not available.\n",
               requested_size);
}

void log_deallocation_success(std::pair<int, int> const& block)
{
    fmt::print("Deallocate success - memory block ({0}-{1}) freed.\n",
               block.first,
               block.second);
}

void log_coalescence(std::pair<int, int> a,
                     std::pair<int, int> b,
                     std::pair<int, int> const& r)
{
    if (a.first > b.first) {
        std::swap(a, b); // sort by block begin for nicer output
    }

    fmt::print("Buddies found: ({}-{})({}-{}). Coalescing to ({}-{})\n",
               a.first,
               a.second,
               b.first,
               b.second,
               r.first,
               r.second);
}

void log_coalescence_stop(std::pair<int, int> const& block)
{
    fmt::print("No free buddy found for block: ({}-{}). Coalescing stop.\n",
               block.first,
               block.second);
}

void log_invalid_deallocate_request(int address)
{
    fmt::print("Sorry, invalid free request: {}\n", address);
}

} // namespace logger
