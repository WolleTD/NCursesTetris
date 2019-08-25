cmake_minimum_required(VERSION 3.14)
project(NCursesTetris)

set(CMAKE_CXX_STANDARD 14)

add_executable(NCursesTetris main.cpp Tetroid.cpp math_utils.cpp NCurses.cpp curses_utils.cpp)
target_link_libraries(NCursesTetris curses)

set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE include-what-you-use)