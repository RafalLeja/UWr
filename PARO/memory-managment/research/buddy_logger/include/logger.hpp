#include <utility> // std::pair

namespace logger
{
// allocate
void log_out_of_memory(int requested_size);

void log_out_of_memory_max_size_exceeded(int requested_size,
                                         std::size_t max_size);
void log_out_of_memory_block_truncated(int requested_size,
                                       int truncated_block_size);
void log_allocation_success(int requested_size,
                            std::pair<int, int> const& block);

// deallocate
void log_deallocation_success(std::pair<int, int> const& block);
void log_coalescence(std::pair<int, int> a,
                     std::pair<int, int> b,
                     std::pair<int, int> const& r);
void log_coalescence_stop(std::pair<int, int> const& block);
void log_invalid_deallocate_request(int address);
} // namespace logger
