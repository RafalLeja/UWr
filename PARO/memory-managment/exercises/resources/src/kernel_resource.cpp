/*This file is good as it is - do not modify it*/

#include "kernel_resource.h"
#include "kernel.h"

#include "printers.h"
#include <exception>
#include <iostream>
#include <map>
#include <random>
#include <utility>
#include <ranges>

struct RESOURCE
{
    int timestamp; // time of allocation
    int usage_count = 0;
};

class Kernel
{
public:
    std::unique_ptr<KernelConfig> config;
    std::unique_ptr<KernelPolicy> policy;

    Kernel(std::unique_ptr<KernelConfig> config,
           std::unique_ptr<KernelPolicy> policy)
        : config(std::move(config)),
          policy(std::move(policy))
    {}

    ~Kernel() noexcept
    {
        if (not allocated_resources.empty()) {
            log_resources_allocated_on_exit(allocated_resources.size());
        }

        if (policy) {
            for (const auto& ptr : allocated_resources | std::views::keys) {
                policy->handle_leaked_resource(ptr);
            }
        }
    }

    RESOURCE* allocate()
    {
        current_time++;

        auto handle = reinterpret_cast<RESOURCE*>(
            config->get_next_resource_id());
        if (config->is_allocation_successful()) {
            auto [_, success] = allocated_resources.emplace(
                handle, RESOURCE{current_time});
            if (success) {
                log_allocation_successfull(handle);
                return handle;
            }
            log_allocation_failed_exception(handle);
            throw kernel_allocation_error();
        }
        log_allocation_failed_null(handle);
        return nullptr;
    }

    void free(RESOURCE* p)
    {
        current_time++;

        if (not p) {
            log_free_null();
            std::terminate();
        }

        const auto it = allocated_resources.find(p);
        const auto& [timestamp, usage_count] = it->second;

        if (allocated_resources.cend() == it) {
            log_free_unallocated(p);
            std::terminate();
        }

        log_free_summary(p, current_time - timestamp, usage_count);

        allocated_resources.erase(it);
    }

    void do_the_trick(RESOURCE* p)
    {
        current_time++;

        if (not p) {
            log_operation_failed_null();
            std::terminate();
        }

        const auto it = allocated_resources.find(p);
        if (allocated_resources.cend() == it) {
            log_operation_failed_unallocated(p);
            std::terminate();
        }

        auto& [_, usage_count] = it->second;

        log_operation_attempt(p);
        usage_count++;

        if (not config->is_operation_successful()) {
            throw kernel_operation_error();
        }
    }

private:
    std::map<RESOURCE*, RESOURCE> allocated_resources;

    int current_time = 0;
};

class RandomKernelConfig : public KernelConfig
{
public:
    RandomKernelConfig(int allocation_fail_ratio,
                       int operation_fail_ratio) noexcept
        : random_engine(std::random_device{}()),
          address_distrib(0x1000, 0x3FFF),
          allocation_success_distrib(1, allocation_fail_ratio),
          operation_success_distrib(1, operation_fail_ratio)
    {}

    int get_next_resource_id() noexcept override
    {
        return address_distrib(random_engine);
    }

    bool is_allocation_successful() noexcept override
    {
        return allocation_success_distrib(random_engine) > 1;
    }

    bool is_operation_successful() noexcept override
    {
        return operation_success_distrib(random_engine) > 1;
    }

private:
    std::minstd_rand random_engine;
    std::uniform_int_distribution<> address_distrib;
    std::uniform_int_distribution<> allocation_success_distrib;
    std::uniform_int_distribution<> operation_success_distrib;
};

class CrashKernelPolicy : public KernelPolicy
{
public:
    void handle_leaked_resource(RESOURCE* p) const override
    {
        log_leaked_resource(p);
        std::terminate();
    }
};

static std::unique_ptr<Kernel> the_kernel = std::make_unique<Kernel>(
    std::make_unique<RandomKernelConfig>(4, 5),
    std::make_unique<CrashKernelPolicy>());

void reconfigure_kernel(std::unique_ptr<KernelConfig> cfg,
                        std::unique_ptr<KernelPolicy> policy)
{
    the_kernel = std::make_unique<Kernel>(std::move(cfg), std::move(policy));
}

void finalize_kernel() { the_kernel.reset(nullptr); }

RESOURCE* allocate_resource() { return the_kernel->allocate(); }
void free_resource(RESOURCE* p) { return the_kernel->free(p); }
void use_resource(RESOURCE* p) { the_kernel->do_the_trick(p); }
