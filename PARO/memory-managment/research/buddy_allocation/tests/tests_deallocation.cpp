#include <buddy/Heap.hpp>

#include <gtest/gtest.h>

using namespace ::testing;

TEST(Deallocation, when_invalid_request_then_do_nothing)
{
    Heap h(64);
    ASSERT_EQ(0x0, h.allocate(32));
    h.deallocate(0x10);
}

TEST(Deallocation, when_deallocated_then_address_can_be_used_again)
{
    Heap h(128);
    ASSERT_EQ(0x0, h.allocate(65));
    h.deallocate(0x0);

    ASSERT_EQ(0x0, h.allocate(65));
}

TEST(Deallocation, when_deallocated_then_can_be_reused_by_smaller_blocks)
{
    Heap h(128);
    ASSERT_EQ(0x0, h.allocate(32));
    ASSERT_EQ(0x20, h.allocate(32));
    ASSERT_EQ(0x40, h.allocate(64));

    h.deallocate(0);

    ASSERT_EQ(0x0, h.allocate(16));
    ASSERT_EQ(0x10, h.allocate(16));
}

TEST(Deallocation, when_deallocated_then_can_be_reused_by_similar_block)
{
    Heap h(128);
    ASSERT_EQ(0x0, h.allocate(32));
    ASSERT_EQ(0x20, h.allocate(32));
    ASSERT_EQ(0x40, h.allocate(64));

    h.deallocate(0x20);

    ASSERT_EQ(0x20, h.allocate(32));
}

TEST(Deallocation,
     when_buddy_blocks_deallocated_then_can_be_merged_into_larger_block)
{
    Heap h(128);
    ASSERT_EQ(0x0, h.allocate(32));
    ASSERT_EQ(0x20, h.allocate(32));
    ASSERT_EQ(0x40, h.allocate(64));

    h.deallocate(0);
    h.deallocate(0x20);

    ASSERT_EQ(0x0, h.allocate(64));
    h.print_free();
    // expected heap availability:
    // [1B:][2B:][4B:][8B:][16B:][32B:][64B:][128B:]
}

TEST(Deallocation, when_no_buddies_deallocate_then_cannot_be_merged)
{
    Heap h(128);
    ASSERT_EQ(0x0, h.allocate(32));
    ASSERT_EQ(0x20, h.allocate(32)); // buddy with 0x0
    ASSERT_EQ(0x40, h.allocate(32)); // buddy with 0x60
    ASSERT_EQ(0x60, h.allocate(32));

    h.deallocate(0x20);
    h.deallocate(0x40);

    ASSERT_EQ(HEAP_NULL, h.allocate(64));
    h.print_free();
    // expected heap availability:
    // [1B:][2B:][4B:][8B:][16B:][32B:(32-63)(64-95)][64B:][128B:]
}

TEST(Deallocation, when_deallocate_then_merge_free_blocks_bottop_up)
{
    Heap h(128);
    ASSERT_EQ(0x0, h.allocate(64));
    ASSERT_EQ(0x40, h.allocate(16));

    h.deallocate(0x0);
    h.print_free();
    // Heap availability:
    // [1B:][2B:][4B:][8B:][16B:(80-95)][32B:(96-127)][64B:(0-63)][128B:]
    h.deallocate(0x40);
    h.print_free();
    // Heap availability: [1B:][2B:][4B:][8B:][16B:][32B:][64B:][128B:(0-127)]

    ASSERT_EQ(0x0, h.allocate(32));
    ASSERT_EQ(0x20, h.allocate(32));
    h.print_free();
    // Heap availability: [1B:][2B:][4B:][8B:][16B:][32B:][64B:(64-127)][128B:]
}

TEST(Deallocation, test_dealocate_to_make_room)
{
    Heap h(128);
    ASSERT_EQ(0x0, h.allocate(32));
    ASSERT_EQ(0x20, h.allocate(32));
    ASSERT_EQ(0x40, h.allocate(32));
    ASSERT_EQ(0x60, h.allocate(32));

    ASSERT_EQ(HEAP_NULL, h.allocate(1)); // memory full

    h.deallocate(64);

    ASSERT_EQ(0x40, h.allocate(16)); // split
    ASSERT_EQ(0x50, h.allocate(16));

    h.deallocate(0x50);
    h.deallocate(0x40); // coalescence 0x40 and 0x50

    ASSERT_EQ(0x40, h.allocate(32)); // use coalescenced block
}
