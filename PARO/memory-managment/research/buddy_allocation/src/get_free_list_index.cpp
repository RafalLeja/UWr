#include <cmath>

int get_free_list_index(int bytes) noexcept
{
    return std::ceil(std::log2(bytes));
}
