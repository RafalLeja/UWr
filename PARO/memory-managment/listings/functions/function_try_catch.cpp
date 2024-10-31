#include <stdexcept>

#include <paro/Integer.hpp>

void throwing(Integer e)
{
    Integer f{'f'};
    throw std::runtime_error("whoops!");
    Integer g{'g'};
}

int main(int argc, char* argv[])
{
    Integer a{'a'}, b{'b'};
    try {
        Integer c{'c'}, d{'d'};
        throwing(Integer('e'));
    } catch (std::runtime_error const& ex) {}
}
