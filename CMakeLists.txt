cmake_minimum_required(VERSION 3.14)
project(NCursesTetris)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE include-what-you-use)

add_executable(NCursesTetris
        main.cpp
        Playground.cpp
        Tetroid.cpp
        math_utils.cpp
        curses_utils.cpp)

target_link_libraries(NCursesTetris curses)
