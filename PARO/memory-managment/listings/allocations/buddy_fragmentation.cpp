#include "Heap.hpp"

void demo_fragmentation()
{
    Heap h(128);

    h.allocate(32);
    h.allocate(64);
    h.allocate(5); // 3 bytes wasted

    h.allocate(20); // fail!

    h.allocate(16); // OK
    h.allocate(8); // OK
}
