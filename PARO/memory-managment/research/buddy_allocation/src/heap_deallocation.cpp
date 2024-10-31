#include "Heap.hpp"

#include <algorithm>

#include <logger.hpp>

namespace
{
// calculate address of sibling block
int buddy_address(int block_start, int block_size)
{
    int block_number = block_start / block_size;
    if (block_number % 2 != 0) {
        return block_start - block_size;
    }
    return block_start + block_size;
}
} // namespace

void Heap::deallocate(int address)
{
    if (mp.find(address) == mp.end()) {
        // block at address was never allocated (or already freed)
        logger::log_invalid_deallocate_request(address);
        return;
    }

    // get position of block to be added to free_list
    const int nth = get_free_list_index(mp.at(address));

    // notify user about block deallocation
    logger::log_deallocation_success(
        std::make_pair(address, mp.at(address) - 1));

    // remove from allocated memory
    mp.erase(address);

    // memory block parameters
    int block_size = (1 << nth); // size normalized to power of 2
    auto block = std::make_pair(address, address + block_size - 1);

    // run coalescence algorithm from freed block position
    auto it = std::next(free_list.begin(), nth);
    while (it != free_list.end()) {
        auto block_it = it->emplace(it->end(), block);

        // find buddy
        auto buddy_it = std::find_if(
            it->begin(),
            it->end(),
            [a = buddy_address(block_it->first, block_size)](
                auto const& block) { return a == block.first; });

        if (buddy_it == it->end()) {
            logger::log_coalescence_stop(block);
            return; // no buddies => no coalescing
        } else {
            // new block in parent scope!
            // Using span arithmetic
            // (a,b) + (c,d) = (min(a,b,c,d), max(a,b,c,d))
            // it _WILL_ fail miserably for overlapping or disjoint regions!

            // calculate new block dimensions
            block = std::minmax({block_it->first,
                                 block_it->second,
                                 buddy_it->first,
                                 buddy_it->second});

            logger::log_coalescence(*block_it, *buddy_it, block);

            { // remove merged buddies from this bucket
                it->erase(block_it);
                it->erase(buddy_it);
            }

            { // update iterators!
                ++it; // check for buddies in parent scope
                block_size *= 2; // double the block size
            }
        }
    }
}
