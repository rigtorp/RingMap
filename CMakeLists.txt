cmake_minimum_required(VERSION 3.8)
project(RingMap LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

enable_testing()

add_library(RingMap INTERFACE)
target_include_directories(RingMap INTERFACE include)

add_executable(RingMapTest test/RingMapTest.cpp)
target_link_libraries(RingMapTest RingMap)
add_test(RingMapTest RingMapTest)