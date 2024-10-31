#include <resources/kernel_resource.h>

#include <stdexcept> // std::runtime_error
#include <iostream>  

void kernel_stress_test()
{
    // will return NULL if:
    // 1. allocation was not successful
    // will THROW std::runtime_error if:
    // 1. sometimes, due to internal reasons (wrap in try-catch!)
    RESOURCE* resource = nullptr;
    try {
        resource = allocate_resource();
    } catch (const std::runtime_error& e) {
        std::cerr << "Failed to allocate resource: " << e.what() << std::endl;
        return;
    }
    if (resource == NULL) {
        std::cerr << "Failed to allocate resource" << std::endl;
        return;
    }

    // will THROW std::runtime_error if:
    // 1. sometimes, with no particular reason (wrap in try-catch!)
    // will CRASH (std::terminate) if:
    // 1. resource is NULL (add NULL-check!)
    // 2. resource was already released
    if (resource != nullptr) {
        try {
            use_resource(resource);
        } catch (const std::runtime_error& e) {
            std::cerr << "Failed to use resource: " << e.what() << std::endl;
            free_resource(resource);
            return;
        }
    } else {
        std::cerr << "Resource is NULL" << std::endl;
        return;
    }

    // will CRASH (std::terminate) if:
    // 1. resource is NULL (add NULL-check!)
    // 2. resource is already released
    if (resource != nullptr) {
        free_resource(resource);
    } else {
        std::cerr << "Resource is NULL" << std::endl;
    }
}

int main(int ac, char* av[])
{
    constexpr int repetitions = 32;

    for (int i = 0; i < repetitions; ++i) { kernel_stress_test(); }

    // the program will CRASH (std::terminate) if:
    // 1. there are resources not yet released on exit
    return 0;
}
