cmake_minimum_required(VERSION 3.18)
project(memory-management-exercises LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

find_program(MEMCHECK valgrind)
set(MEMCHECK_OPTIONS --tool=memcheck --leak-check=full --error-exitcode=1 --errors-for-leak-kinds=all)
set(FDS_OPTIONS -q --tool=none --track-fds=yes)

enable_testing()

add_subdirectory(resources)

# EXERCISES
add_executable(example_leak example_leak.cpp)
add_test(NAME task1-leak COMMAND ${MEMCHECK} ${MEMCHECK_OPTIONS} ./example_leak)

add_executable(example_leak_array example_leak_array.cpp)
add_test(NAME task2-leak-array COMMAND ${MEMCHECK} ${MEMCHECK_OPTIONS} ./example_leak_array)

add_executable(example_leak_exception example_leak_exception.cpp)
target_link_libraries(example_leak_exception PRIVATE kernel-resource)
add_test(NAME task3-leak-exception COMMAND ${MEMCHECK} ${MEMCHECK_OPTIONS} ./example_leak_exception)

add_executable(example_leak_raii example_leak_raii.cpp)
target_link_libraries(example_leak_raii PRIVATE kernel-resource)
add_test(NAME task4-leak-raii COMMAND ${MEMCHECK} ${MEMCHECK_OPTIONS} ./example_leak_raii)

add_executable(example_leak_fds example_leak_fds.cpp)
add_test(NAME task5-leak-fds COMMAND ${MEMCHECK} ${FDS_OPTIONS} ./example_leak_fds)
set_tests_properties(task5-leak-fds PROPERTIES FAIL_REGULAR_EXPRESSION "Open file descriptor [0-9]+: log.txt")
