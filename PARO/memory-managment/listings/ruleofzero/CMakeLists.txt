add_executable(ruleofzero_only_destructor example_only_destructor.cpp)
add_executable(ruleofzero_ruleoffive example_ruleoffive.cpp)
add_executable(ruleofzero_ruleofthree example_ruleofthree.cpp)
add_executable(ruleofzero_ruleofzero example_ruleofzero.cpp)

# add_test(NAME ruleofzero_only_destructor COMMAND ruleofzero_only_destructor)
add_test(NAME ruleofzero_ruleoffive COMMAND ruleofzero_ruleoffive)
add_test(NAME ruleofzero_ruleofthree COMMAND ruleofzero_ruleofthree)
add_test(NAME ruleofzero_ruleofzero COMMAND ruleofzero_ruleofzero)
