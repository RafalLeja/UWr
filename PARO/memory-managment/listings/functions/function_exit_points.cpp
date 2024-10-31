#include <paro/Object.hpp>

void leak_exit_scope(int param)
{
    Object* obj = new Object(3, 14, param);
    store_result(obj->method());
} // whoops!

int leak_exit_return(int param)
{
    Object* obj = new Object(3, 14, param);
    if (obj->is_odd())
        return obj->method(); // whoops!
    delete obj;
    return 7;
}

int leak_exit_exception(int param)
{
    Object* obj = new Object(3, 14, param);
    if (obj->is_odd())
        throw std::runtime_error("odd param"); // whoops!
    int value = obj->method();
    delete obj;
    return value;
}

int main(int ac, char* av[])
try {
    leak_exit_scope(8);
    leak_exit_return(7);
    leak_exit_exception(19);

    return 0;
} catch (std::runtime_error const& ex) {
    std::cout << "exception raised: " << ex.what() << std::endl;
}
