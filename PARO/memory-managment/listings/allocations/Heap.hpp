#pragma once

struct Heap
{
    Heap(int size);

    int allocate(int size);
    void deallocate(int address);
};

void demo_fragmentation();

void demo_deallocation_1();
void demo_deallocation_2();
