#pragma once

#include <cstddef>

struct RESOURCE;

void log_resources_allocated_on_exit(std::size_t count) noexcept;
void log_leaked_resource(RESOURCE* resource) noexcept;
void log_allocation_successfull(RESOURCE* resource) noexcept;
void log_allocation_failed_exception(RESOURCE* resource) noexcept;
void log_allocation_failed_null(RESOURCE* resource) noexcept;
void log_free_null() noexcept;
void log_free_unallocated(RESOURCE* resource) noexcept;
void log_free_summary(RESOURCE* resource,
                      std::size_t lifetime,
                      std::size_t usage_count) noexcept;
void log_operation_failed_null() noexcept;
void log_operation_failed_unallocated(RESOURCE* resource) noexcept;
void log_operation_attempt(RESOURCE* resource) noexcept;
