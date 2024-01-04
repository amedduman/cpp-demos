cmake_minimum_required(VERSION 3.27)
project(demo)

set(CMAKE_CXX_STANDARD 23)

add_executable(demo main.cpp Demo.h
        Paddle.h
        Ball.h)

find_package(SFML 2.5 COMPONENTS window graphics REQUIRED)
target_link_libraries(demo sfml-window sfml-graphics)
