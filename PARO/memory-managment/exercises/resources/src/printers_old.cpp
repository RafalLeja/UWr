#include "printers.h"

#include <iomanip>
#include <iostream>

long get_id(RESOURCE* r) noexcept
{
    return reinterpret_cast<std::ptrdiff_t>(r);
}

void log_resources_allocated_on_exit(std::size_t count) noexcept
{
    std::cout << "[KERNEL] WARN: " << std::dec << count
              << " resources still allocated on exit." << std::endl;
}

void log_leaked_resource(RESOURCE* resource) noexcept
{

    std::cout << "[KERNEL] CRIT: RESOURCE 0x" << std::hex << get_id(resource)
              << " was not released!" << std::endl;
}

void log_allocation_successfull(RESOURCE* resource) noexcept
{
    std::cout << "[KERNEL] INF: RESOURCE 0x" << std::hex << get_id(resource)
              << " allocation successful" << std::endl;
}

void log_allocation_failed_exception(RESOURCE* resource) noexcept
{
    std::cout << "[KERNEL] ERR: RESOURCE 0x" << std::hex << get_id(resource)
              << " allocation failed - throw exception" << std::endl;
}

void log_allocation_failed_null(RESOURCE* resource) noexcept
{
    std::cout << "[KERNEL] ERR: RESOURCE 0x" << std::hex << get_id(resource)
              << " allocation failed - return NULL" << std::endl;
}

void log_free_null() noexcept
{
    std::cout << "[KERNEL] CRIT: Cannot free NULL resource!" << std::endl;
}

void log_free_unallocated(RESOURCE* resource) noexcept
{
    std::cout << "[KERNEL] CRIT: Cannot free UNALLOCATED resource "
              << get_id(resource) << "!" << std::endl;
}

void log_free_summary(RESOURCE* resource,
                      std::size_t lifetime,
                      std::size_t usage_count) noexcept
{
    std::cout << "[KERNEL] INF: RESOURCE 0x" << std::hex << get_id(resource)
              << " released." << std::endl;
    std::cout << "[KERNEL] INF:   lifetime: " << std::dec << std::setw(6)
              << lifetime << " ticks" << std::endl;
    std::cout << "[KERNEL] INF:   usage count: " << std::dec << std::setw(3)
              << usage_count << std::endl;
}

void log_operation_failed_null() noexcept
{
    std::cout << "[KERNEL] CRIT: Cannot operate on NULL resource!" << std::endl;
}

void log_operation_failed_unallocated(RESOURCE* resource) noexcept
{
    std::cout << "[KERNEL] CRIT: Cannot operate on UNALLOCATED resource "
              << get_id(resource) << "!" << std::endl;
}

void log_operation_attempt(RESOURCE* resource) noexcept
{
    std::cout << "[KERNEL] INF: RESOURCE 0x" << std::hex << get_id(resource)
              << " usage requested." << std::endl;
}
