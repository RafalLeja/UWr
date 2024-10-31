#include "Heap.hpp"

#include <cstdlib> // std::calloc

Heap::Heap(int capacity)
    : free_list(1 + get_free_list_index(capacity)),
      _memory(std::calloc(capacity, sizeof(char))),
      _sz(capacity)
{
    // single block of specified size is available at the beginning
    free_list.back().emplace_back(0, capacity - 1);
}

Heap::~Heap() { std::free(_memory); }
