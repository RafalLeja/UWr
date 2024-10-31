#include "printers.h"

#include <print>

long get_id(RESOURCE* r) noexcept
{
    return reinterpret_cast<std::ptrdiff_t>(r);
}

void log_resources_allocated_on_exit(std::size_t count) noexcept
{
    std::println("[KERNEL] WARN: {:d} resources still allocated on exit.",
                 count);
}

void log_leaked_resource(RESOURCE* resource) noexcept
{
    std::println("[KERNEL] CRITICAL:  RESOURCE 0x{:4X} was not released!",
                 get_id(resource));
}

void log_allocation_successfull(RESOURCE* resource) noexcept
{
    std::println("[KERNEL] INF: RESOURCE 0x{:4X} allocation successful",
                 get_id(resource));
}

void log_allocation_failed_exception(RESOURCE* resource) noexcept
{
    std::println("[KERNEL] ERR: RESOURCE 0x{:4X} allocation failed - "
                 "throw exception",
                 get_id(resource));
}

void log_allocation_failed_null(RESOURCE* resource) noexcept
{
    std::println(
        "[KERNEL] ERR: RESOURCE 0x{:4X} allocation failed - return NULL",
        get_id(resource));
}

void log_free_null() noexcept
{
    std::println("[KERNEL] CRIT: Cannot free NULL resource!");
}

void log_free_unallocated(RESOURCE* resource) noexcept
{
    std::println("[KERNEL] CRIT: Cannot free UNALLOCATED resource {}!",
                 get_id(resource));
}

void log_free_summary(RESOURCE* resource,
                      std::size_t lifetime,
                      std::size_t usage_count) noexcept
{
    std::println("[KERNEL] INF: RESOURCE 0x{:4X} released.", get_id(resource));
    std::println("[KERNEL] INF:   lifetime: {:6} ticks", lifetime);
    std::println("[KERNEL] INF:   usage count: {:3}", usage_count);
}

void log_operation_failed_null() noexcept
{
    std::println("[KERNEL] CRIT: Cannot operate on NULL resource!");
}

void log_operation_failed_unallocated(RESOURCE* resource) noexcept
{
    std::println("[KERNEL] CRIT: Cannot operate on UNALLOCATED resource!");
}

void log_operation_attempt(RESOURCE* resource) noexcept
{
    std::println("[KERNEL] INF: RESOURCE 0x{:4X} usage requested.",
                 get_id(resource));
}
