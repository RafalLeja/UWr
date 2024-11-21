cmake_minimum_required(VERSION 3.10)
project(PARO-Parallel CXX)

add_definitions(-Wall)
add_definitions(-std=c++20)

# ignore some warning for demos
add_definitions(-Wno-unused-variable)
add_definitions(-Wno-unused-but-set-variable)

# keep this inclusion high, so that external libs can be compiled with all the optimizations!
add_subdirectory(external)
include_directories(external)


if(DEFINED ENV{USE_TSAN})
    set(USE_TSAN "$ENV{USE_TSAN}")
else()
    set(USE_TSAN false)
endif()

# general debug info
add_definitions(-g3)

# some flags for thread sanitization
if(${USE_TSAN})
    message(STATUS "enabling thread sanitizer")
    add_definitions(-fsanitize=thread)
    add_definitions(-fPIC)
    set(CMAKE_CXX_LINK_FLAGS -pie)
    set(sanitizer_link_libs tsan)
endif()

# pthread must always be present (-lpthread does not work for all versions of GCC)
add_definitions(-pthread)
set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -pthread")

# for testing pursposes only
if(EXISTS "${CMAKE_SOURCE_DIR}/przykladowe_rozwiazania")
    message(STATUS "enabling przykladowe_rozwiazania")
    add_subdirectory(przykladowe_rozwiazania)
endif()


add_executable(podstawowa_synchronizacja podstawowa_synchronizacja.cpp)
target_link_libraries(podstawowa_synchronizacja ${sanitizer_link_libs})

add_executable(przekazywanie_przez_kolejke przekazywanie_przez_kolejke.cpp)
target_link_libraries(przekazywanie_przez_kolejke external ${sanitizer_link_libs})

add_executable(stworzenie_watku stworzenie_watku.cpp)
target_link_libraries(stworzenie_watku ${sanitizer_link_libs})

add_executable(argumenty_watku argumenty_watku.cpp)
target_link_libraries(argumenty_watku ${sanitizer_link_libs})

add_executable(wyjatki wyjatki.cpp)
target_link_libraries(wyjatki ${sanitizer_link_libs})

add_executable(obiad obiad.cpp)
target_link_libraries(obiad ${sanitizer_link_libs})

add_executable(promise promise.cpp)
target_link_libraries(promise ${sanitizer_link_libs})
