#include <resources/kernel_resource.h>

#include <iostream>
#include <vector>

#include <memory> // std::unique_ptr

struct Event
{
    int event_id;
};

Event* create_event(int event_id) noexcept { return new Event{event_id}; }

void process_init(RESOURCE* resource) noexcept
try {
    if (resource) {
        use_resource(resource);
        free_resource(resource);
    }
} catch (std::runtime_error const& ex) {
    std::cout << ex.what() << std::endl;
}

void process_event(const Event* event,
                   RESOURCE* temp_resource,
                   RESOURCE* proc_resource) noexcept
try {
    std::cout << "Processing Event(" << event->event_id << ")" << std::endl;

    if (temp_resource) {
        use_resource(temp_resource);
        free_resource(temp_resource);
    }

    if (proc_resource) {
        use_resource(proc_resource);
    }

    delete event;
} catch (std::runtime_error const& ex) {
    std::cout << ex.what() << std::endl;
}

int main(int ac, char* av[])
{
    auto init_resource = allocate_resource();
    process_init(init_resource);

    auto proc_resource = allocate_resource();

    std::vector simulation = {
        12, 24, 36, 48, 60, 72, 84, 96, 108, 120, 132, 144};
    for (auto id : simulation) {
        auto event = create_event(id);
        auto temp_resource = allocate_resource();
        process_event(event, temp_resource, proc_resource);
    }

    if (proc_resource) {
        free_resource(proc_resource);
    }

    return 0;
}
