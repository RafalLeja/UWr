add_library(kernel-resource src/kernel_resource.cpp)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_sources(kernel-resource PRIVATE
        $<$<VERSION_LESS:$<CXX_COMPILER_VERSION>,14.0.0>:${CMAKE_CURRENT_SOURCE_DIR}/src/printers_old.cpp>
        $<$<VERSION_GREATER_EQUAL:$<CXX_COMPILER_VERSION>,14.0.0>:${CMAKE_CURRENT_SOURCE_DIR}/src/printers_new.cpp>)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_sources(kernel-resource PRIVATE
        $<$<VERSION_LESS:$<CXX_COMPILER_VERSION>,18.0.0>:${CMAKE_CURRENT_SOURCE_DIR}/src/printers_old.cpp>
        $<$<VERSION_GREATER_EQUAL:$<CXX_COMPILER_VERSION>,18.0.0>:${CMAKE_CURRENT_SOURCE_DIR}/src/printers_new.cpp>)
else()
    target_sources(kernel-resource PRIVATE src/printers_old.cpp)
endif()

target_include_directories(kernel-resource PUBLIC include PRIVATE src include/resources)

add_subdirectory(tests)
