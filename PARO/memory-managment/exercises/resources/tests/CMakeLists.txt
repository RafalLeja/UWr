find_package(GTest REQUIRED)

add_executable(test_kernel_resource test_kernel_resource.cpp)
target_link_libraries(test_kernel_resource PRIVATE kernel-resource GTest::gmock_main)
target_include_directories(test_kernel_resource PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME test_kernel_resource COMMAND test_kernel_resource)
