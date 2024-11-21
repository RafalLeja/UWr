#include <cmath>
#include "isPrime.hpp"

bool isPrime(const unsigned n)
{
  if(n<2)
    return false;

  const auto max = unsigned{ static_cast<unsigned>(sqrt(n)) + 1u };
  for(unsigned i=2; i<=max; ++i)
    if( (n%i) == 0u )
      return false;

  return true;
}
