cmake_minimum_required(VERSION 3.16)
project(Midpoint_displacement)

set(CMAKE_CXX_STANDARD 14)
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
find_package(Qt5Core REQUIRED)

add_executable(Midpoint_displacement main.cpp)

target_link_libraries(Midpoint_displacement sfml-graphics sfml-audio)
target_link_libraries(Midpoint_displacement Qt5::Core)