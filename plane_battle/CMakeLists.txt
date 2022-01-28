cmake_minimum_required(VERSION 3.20)
project(planes_battle)

set(CMAKE_CXX_STANDARD 20)

add_executable(planes_battle WIN32 main.cpp prog4.cpp prog4.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR D:/SFML/lib/cmake/SFML)
find_package(SFML 2.5 COMPONENTS window graphics audio REQUIRED)
include_directories(D:/SFML/include)

target_link_libraries(planes_battle sfml-window sfml-graphics sfml-audio)