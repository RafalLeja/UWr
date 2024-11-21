cmake_minimum_required(VERSION 2.8)
add_definitions(-DNDEBUG)
add_definitions(-fPIC)

add_library(external
  isPrime.cpp
)
