#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <future>
#include <mutex>

using namespace std::chrono_literals;

std::string time()
{
    static auto start = std::chrono::steady_clock::now();
    std::chrono::duration<double> d = std::chrono::steady_clock::now() - start;
    return "[" + std::to_string(d.count()) + "s]";
}

void producer(std::promise<int> p)
{
    std::this_thread::sleep_for(200ms);
    p.set_value(42);
//    p.set_exception(std::make_exception_ptr(std::runtime_error("Sth goes wrong")));
}

void consumer(std::future<int>& f)
{
    try
    {
        auto data = f.get();
        std::cout << "Consumed data: " << data << std::endl;
    }
    catch (const std::exception& ex)
    {
        std::cout << "Exception caught: " << ex.what() << std::endl;
    }
}

int main()
{
    std::cout << time() << " Start\n";

    std::promise<int> promise;
    auto future = promise.get_future();

    std::thread p(producer, std::move(promise));
    std::thread c(consumer, std::ref(future));

    p.join();
    c.join();

    std::cout << time() << " End\n";

    return 0;
}
