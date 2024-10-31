#pragma once

#include <map>
#include <vector>

constexpr int HEAP_NULL = -1; // 0 is valid address here

struct Heap
{
    explicit Heap(int capacity);
    ~Heap();

    int allocate(int req_size);
    void deallocate(int address);

    void print_allocated() const noexcept;
    void print_free() const noexcept;
    void print_memory() const noexcept;

    template <typename T> T* ref(int ptr) const noexcept
    {
        return reinterpret_cast<T*>((char*)_memory + ptr);
    }

private:
    std::vector<std::vector<std::pair<int, int>>> free_list; // the heap

    std::map<int, int> mp; // allocated memory blocks - use in deallocation

    void* _memory; // "true" memory page
    int _sz; // and page size (in bytes)
};

// exponent of the smallest power of two not less than requested size
int get_free_list_index(int bytes) noexcept;
