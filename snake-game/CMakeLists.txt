cmake_minimum_required(VERSION 3.27)
project(demo)

set(CMAKE_CXX_STANDARD 23)

add_executable(demo main.cpp demo.h
        Cell.h
        Snake.h
        SnakeSegment.h
        Grid.h)

find_package(SFML 2.5 COMPONENTS window graphics REQUIRED)
target_link_libraries(demo sfml-window sfml-graphics)
