#include <buddy/Heap.hpp>

#include <gtest/gtest.h>

using namespace ::testing;

TEST(Allocation, test_heap_null_is_constant) { ASSERT_EQ(HEAP_NULL, -1); }

TEST(Allocation, test_cannot_allocate_more_than_reserved_block)
{
    Heap h(64);
    h.print_free();
    // allocation failed due to top block overflow
    ASSERT_EQ(HEAP_NULL, h.allocate(65));
}

TEST(Allocation, test_cannot_allocate_more_than_reserved)
{
    Heap h(65);
    h.print_free();
    // failed due to max capacity exceeded in truncated block
    ASSERT_EQ(HEAP_NULL, h.allocate(67));
}

TEST(Allocation, test_nonrecoverable_overallocation)
{
    Heap h(256);
    ASSERT_EQ(0, h.allocate(129));
    ASSERT_EQ(HEAP_NULL, h.allocate(1));
    h.print_free();
}

TEST(Allocation, test_fragmentation)
{
    Heap h(128);
    h.print_free();
    ASSERT_EQ(0, h.allocate(32));
    ASSERT_EQ(32, h.allocate(5));
    ASSERT_EQ(64, h.allocate(64));

    h.print_allocated();

    ASSERT_EQ(HEAP_NULL, h.allocate(20));
    h.print_free();
    ASSERT_EQ(48, h.allocate(16));
    ASSERT_EQ(40, h.allocate(8));

    h.print_allocated();
}
