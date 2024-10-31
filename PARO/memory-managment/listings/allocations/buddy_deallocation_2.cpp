#include "Heap.hpp"

void demo_deallocation_2()
{
    Heap h(128);

    h.allocate(16);
    h.allocate(16);
    h.allocate(16);
    h.allocate(16);

    h.deallocate(16);
    h.deallocate(32);
    h.deallocate(0); // coalescing
}
