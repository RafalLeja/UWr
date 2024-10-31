if (GTest_FOUND)
    add_executable(buddy_allocation_ut tests_allocation.cpp)
    target_link_libraries(buddy_allocation_ut PRIVATE buddy-allocation GTest::gtest_main)
    add_test(NAME buddy_allocation_ut COMMAND buddy_allocation_ut)

    add_executable(buddy_deallocation_ut tests_deallocation.cpp)
    target_link_libraries(buddy_deallocation_ut PRIVATE buddy-allocation GTest::gtest_main)
    add_test(NAME buddy_deallocation_ut COMMAND buddy_deallocation_ut)
endif()
