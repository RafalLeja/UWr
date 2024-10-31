set(SOURCES
    src/Heap.cpp
    src/heap_print.cpp
    src/heap_allocation.cpp
    src/heap_deallocation.cpp
    src/get_free_list_index.cpp
)

add_library(buddy-allocation ${SOURCES})
target_link_libraries(buddy-allocation PRIVATE buddy-logger)
target_include_directories(buddy-allocation PUBLIC include PRIVATE include/buddy src)

add_subdirectory(tests)
