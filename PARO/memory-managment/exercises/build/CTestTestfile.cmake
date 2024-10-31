# CMake generated Testfile for 
# Source directory: /home/rafal/Desktop/UWr/PARO/memory-managment/exercises
# Build directory: /home/rafal/Desktop/UWr/PARO/memory-managment/exercises/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(task1-leak "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=full" "--error-exitcode=1" "--errors-for-leak-kinds=all" "./example_leak")
set_tests_properties(task1-leak PROPERTIES  _BACKTRACE_TRIPLES "/home/rafal/Desktop/UWr/PARO/memory-managment/exercises/CMakeLists.txt;17;add_test;/home/rafal/Desktop/UWr/PARO/memory-managment/exercises/CMakeLists.txt;0;")
add_test(task2-leak-array "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=full" "--error-exitcode=1" "--errors-for-leak-kinds=all" "./example_leak_array")
set_tests_properties(task2-leak-array PROPERTIES  _BACKTRACE_TRIPLES "/home/rafal/Desktop/UWr/PARO/memory-managment/exercises/CMakeLists.txt;20;add_test;/home/rafal/Desktop/UWr/PARO/memory-managment/exercises/CMakeLists.txt;0;")
add_test(task3-leak-exception "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=full" "--error-exitcode=1" "--errors-for-leak-kinds=all" "./example_leak_exception")
set_tests_properties(task3-leak-exception PROPERTIES  _BACKTRACE_TRIPLES "/home/rafal/Desktop/UWr/PARO/memory-managment/exercises/CMakeLists.txt;24;add_test;/home/rafal/Desktop/UWr/PARO/memory-managment/exercises/CMakeLists.txt;0;")
add_test(task4-leak-raii "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=full" "--error-exitcode=1" "--errors-for-leak-kinds=all" "./example_leak_raii")
set_tests_properties(task4-leak-raii PROPERTIES  _BACKTRACE_TRIPLES "/home/rafal/Desktop/UWr/PARO/memory-managment/exercises/CMakeLists.txt;28;add_test;/home/rafal/Desktop/UWr/PARO/memory-managment/exercises/CMakeLists.txt;0;")
add_test(task5-leak-fds "/usr/bin/valgrind" "-q" "--tool=none" "--track-fds=yes" "./example_leak_fds")
set_tests_properties(task5-leak-fds PROPERTIES  FAIL_REGULAR_EXPRESSION "Open file descriptor [0-9]+: log.txt" _BACKTRACE_TRIPLES "/home/rafal/Desktop/UWr/PARO/memory-managment/exercises/CMakeLists.txt;31;add_test;/home/rafal/Desktop/UWr/PARO/memory-managment/exercises/CMakeLists.txt;0;")
subdirs("resources")
