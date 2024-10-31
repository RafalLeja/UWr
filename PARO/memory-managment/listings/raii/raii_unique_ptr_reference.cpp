#include <paro/Data.h>

std::unique_ptr<Data> load_initial_config();
void startup(std::unique_ptr<Data> const& init_cfg);

int main(int argc, const char* argv[])
{
    auto init_cfg = load_initial_config();
    startup(init_cfg); // init_cfg is NOT released

    for (EVER) {
        auto event = event_queue.front();
        process(event);
    }

    // many events later...
    return 0; // init_cfg is released here
}

std::unique_ptr<Data> load_initial_config()
{
    return std::make_unique<Data>(0x111);
}

void startup(std::unique_ptr<Data> const& init_cfg)
{
    // perform initial configuration
}
