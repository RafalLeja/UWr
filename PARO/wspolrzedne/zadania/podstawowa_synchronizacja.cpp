#include <thread>
#include <vector>
#include <string>
#include <typeinfo>
#include <iostream>
#include <sstream>

std::string output;

void addLines(unsigned count, std::mutex& mtx)
{
  std::ostringstream ss;
  ss << std::this_thread::get_id();


  for(unsigned i=0; i<count; ++i)
  {
	
		std::lock_guard<std::mutex> lock(mtx);
		/* mtx.lock(); */
    output += ss.str();
    output += ": #";
    output += std::to_string(i);
    output += "\n";
	
		/* mtx.unlock(); */
  }

}


int main()
{
  try
  {
    constexpr auto threadsCount = 3;
    constexpr auto iterations   = 40;

    std::vector<std::thread> threads;
    threads.reserve(threadsCount);

		std::mutex mtx;
    for(auto i=0; i<threadsCount; ++i)
      threads.emplace_back(addLines, iterations, std::ref(mtx));

    for(auto& th: threads)
      th.join();

    std::cout << output << std::endl;
  }
  catch(std::exception const &ex)
  {
    std::cerr << "Oops: " << ex.what() << " (" << typeid(ex).name() << ")" << std::endl;
    return 42;
  }
}
