#include <paro/Data.h>

std::unique_ptr<Data> load_config() noexcept;
void startup(Data const& cfg) noexcept;

int main(int ac, const char* av[])
{
    auto cfg = load_config();
    startup(*cfg);

    for (EVER) {
        auto event = event_queue.front();
        process(event, *cfg);
    }

    return 0;
}
