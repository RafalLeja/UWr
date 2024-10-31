/*This file is good as it is - do not modify it*/

#pragma once

#include <memory>
#include <stdexcept>

struct RESOURCE;

class KernelConfig
{
public:
    virtual ~KernelConfig() = default;

    virtual int get_next_resource_id() noexcept = 0;
    virtual bool is_allocation_successful() noexcept = 0;
    virtual bool is_operation_successful() noexcept = 0;
};

class KernelPolicy
{
public:
    virtual ~KernelPolicy() = default;

    virtual void handle_leaked_resource(RESOURCE*) const = 0;
};

struct kernel_allocation_error : std::runtime_error
{
    kernel_allocation_error()
        : std::runtime_error(
              "Resource allocation failed, identifier pool exhausted.")
    {}
};

struct kernel_operation_error : std::runtime_error
{
    kernel_operation_error()
        : std::runtime_error(
              "Resource is ok, but operation has failed on system-level.")
    {}
};

void reconfigure_kernel(std::unique_ptr<KernelConfig> cfg,
                        std::unique_ptr<KernelPolicy> policy);

void finalize_kernel();
