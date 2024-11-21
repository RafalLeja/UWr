#include <thread>
#include <typeinfo>
#include <iostream>
#include "Queue.hpp"
#include "isPrime.hpp"
#include <condition_variable>

constexpr auto range = 1000u*1000u;
Queue queue;


void producer(std::mutex& mtx, std::condition_variable& cv)
{
  for(unsigned i=0; i<range; ++i) {
		std::lock_guard<std::mutex> lock(mtx);
    queue.push( Queue::value_type{i, isPrime(i)} );
		cv.notify_one();
	}
}


void consumer(std::mutex& mtx, std::condition_variable& cv)
{
  for(unsigned i=0; i<range; ++i)
  {
		std::unique_lock<std::mutex> lock(mtx);
		cv.wait(lock, []{ return !queue.empty(); });
    /* while( queue.empty() ) */
    /* { } */
    const auto e = queue.pop();
    std::cout << e.n_ << " is " << (e.isPrime_?"":"not ") << "a prime number" << std::endl;
  }
}


int main()
{
  try
  {
		std::mutex mtx;
		std::condition_variable cv;
    std::thread prod(producer, std::ref(mtx), std::ref(cv));
    std::thread cons(consumer, std::ref(mtx), std::ref(cv));
    prod.join();
    cons.join();
  }
  catch(std::exception const &ex)
  {
    std::cerr << "Oops: " << ex.what() << " (" << typeid(ex).name() << ")" << std::endl;
    return 42;
  }
}
