cmake_minimum_required(VERSION 3.20)
project(prog4)

add_executable(prog4 main.cpp prog4.cpp prog4.h)

project(prog4_my_vector)
add_executable(prog4_my_vector main.cpp prog4.cpp prog4.h my_vector.h)

project(test)
### googletest init ###
include(FetchContent)
FetchContent_Declare(
        googletest

        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
### googletest init end ###

add_executable(test test.cpp prog4.cpp prog4.h)
target_link_libraries(test gtest_main)

