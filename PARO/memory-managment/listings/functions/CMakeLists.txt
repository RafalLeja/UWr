add_executable(function_scope function_scope.cpp)
target_compile_options(function_scope PRIVATE -Wno-return-local-addr)
add_test(NAME function_scope COMMAND function_scope)

add_executable(function_invalid_scope function_invalid_scope.cpp)
target_compile_options(function_invalid_scope PRIVATE -Wno-return-local-addr)
add_test(NAME function_invalid_scope COMMAND function_invalid_scope)

add_executable(function_cstring function_cstring.cpp)
add_test(NAME function_cstring COMMAND function_cstring)
add_executable(function_cstring_fix function_cstring_fix.cpp)
add_test(NAME function_cstring_fix COMMAND function_cstring_fix)

add_executable(function_exit_points function_exit_points.cpp)
target_link_libraries(function_exit_points PRIVATE paro)
add_test(NAME function_exit_points COMMAND function_exit_points)

add_executable(function_try_catch function_try_catch.cpp)
add_test(NAME function_try_catch COMMAND function_try_catch)
target_link_libraries(function_try_catch PRIVATE paro)
