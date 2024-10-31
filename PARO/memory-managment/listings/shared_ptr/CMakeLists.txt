add_executable(make_shared_leak shared_ptr_function_call_leak.cpp)
target_link_libraries(make_shared_leak PRIVATE paro)
add_test(NAME make_shared_leak COMMAND make_shared_leak)

add_executable(make_shared_no_leak shared_ptr_function_call_no_leak.cpp)
target_link_libraries(make_shared_no_leak PRIVATE paro)
add_test(NAME make_shared_no_leak COMMAND make_shared_no_leak)

add_executable(raii_shared_ptr shared_ptr_deleter.cpp)
target_link_libraries(raii_shared_ptr PRIVATE paro)
add_test(NAME raii_shared_ptr COMMAND raii_shared_ptr)

add_executable(shared_ptr_resource shared_ptr_resource.cpp)
target_link_libraries(shared_ptr_resource PRIVATE paro)
add_test(NAME shared_ptr_resource COMMAND shared_ptr_resource)

#add_executable(shared_ptr_aliasing shared_ptr_aliasing.cpp)
#target_link_libraries(shared_ptr_aliasing PRIVATE paro)
#add_test(NAME shared_ptr_aliasing COMMAND shared_ptr_aliasing)

add_executable(weak_ptr_cycle weak_ptr_cycle.cpp)
add_test(NAME weak_ptr_cycle COMMAND weak_ptr_cycle)

add_executable(weak_ptr_no_cycle weak_ptr_no_cycle.cpp)
add_test(NAME weak_ptr_no_cycle COMMAND weak_ptr_no_cycle)

add_executable(weak_ptr_expired weak_ptr_expired.cpp)
add_test(NAME weak_ptr_expired COMMAND weak_ptr_expired)
