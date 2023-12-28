cmake_minimum_required(VERSION 3.27)
project(starter)

set(CMAKE_CXX_STANDARD 23)

add_executable(starter main.cpp
        StarterDemo.h)

find_package(SFML 2.5 COMPONENTS window graphics REQUIRED)
target_link_libraries(starter sfml-window sfml-graphics)
