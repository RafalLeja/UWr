add_library(paro src/Object.cpp src/Integer.cpp src/Resource.cpp src/File.cpp)
target_include_directories(paro PUBLIC include PRIVATE include/paro)
