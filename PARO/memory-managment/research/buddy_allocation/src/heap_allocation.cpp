#include "Heap.hpp"

#include <algorithm>

#include <logger.hpp>

namespace
{
int block_size(std::pair<int, int> block)
{
    return block.second - block.first + 1;
}

std::pair<int, int> behead(std::vector<std::pair<int, int>>& v)
{
    auto tmp = v.front();
    v.erase(v.begin());
    return tmp;
}
} // namespace

int Heap::allocate(int req_size)
{
    if (req_size < 1) {
        // cannot process request for 0 length
        return HEAP_NULL;
    }

    int n = get_free_list_index(req_size); // find position in heap
    if (n >= free_list.size()) {
        logger::log_out_of_memory_max_size_exceeded(req_size, free_list.size());
        return HEAP_NULL;
    }

    const auto it_n = std::next(free_list.begin(), n);
    if (not it_n->empty()) {
        // There is a free block that requested size simply fits in
        int bs = block_size(it_n->front());
        if (bs < req_size) {
            // special case: page size is not equal to power of two
            // and requested size is greater than size of such
            // truncated block
            logger::log_out_of_memory_block_truncated(req_size, bs);
            return HEAP_NULL;
        }

        auto tmp = behead(*it_n); // remove block from free_list(heap)
        logger::log_allocation_success(req_size, tmp);
        mp[tmp.first] = block_size(tmp); // store for deallocation
        return tmp.first; // return address of block to client code
    } else {
        // Find the smallest free block with size greater than requested
        // ...[4:] [8:] [16:] [32:(32-63)]
        // ...     req ---------^ - found!
        auto it = std::find_if(std::next(it_n, +1),
                               free_list.end(),
                               [](const auto& free_n_blocks) {
                                   return not free_n_blocks.empty();
                               });

        // and split it in half
        if (it != free_list.end()) {
            auto tmp = behead(*it);

            // until the size is appropriate
            while (--it >= it_n) {
                // go back - split current block in half
                auto lo = std::make_pair(
                    tmp.first, tmp.first + (tmp.second - tmp.first) / 2);
                auto hi = std::make_pair(
                    tmp.first + (tmp.second - tmp.first + 1) / 2, tmp.second);

                it->push_back(lo); // push first block to back
                it->push_back(hi);
                tmp = behead(*it); // pop block (might be different than first)
            }

            logger::log_allocation_success(req_size, tmp);
            mp[tmp.first] = block_size(tmp); // store for deallocation
            return tmp.first; // return address of block to client code
        } else {
            // no free block of requested size available!
            logger::log_out_of_memory(req_size);
            return HEAP_NULL;
        }
    }
}
