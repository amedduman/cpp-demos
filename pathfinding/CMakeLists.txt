cmake_minimum_required(VERSION 3.27)
project(pathfinding)

set(CMAKE_CXX_STANDARD 23)

add_executable(pathfinding main.cpp
        PathfindingDemo.h)

find_package(SFML 2.5 COMPONENTS window graphics REQUIRED)
target_link_libraries(pathfinding sfml-window sfml-graphics)
