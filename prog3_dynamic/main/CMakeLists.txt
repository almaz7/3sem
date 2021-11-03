cmake_minimum_required(VERSION 3.20)
project(main)

set(CMAKE_CXX_STANDARD 20)

add_executable(main main.cpp)

include_directories(../lab3library)

target_link_libraries(main lab3library)