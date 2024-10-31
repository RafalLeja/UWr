add_library(buddy-logger STATIC src/logger.cpp)
target_include_directories(buddy-logger PUBLIC include PRIVATE include/logger src)
