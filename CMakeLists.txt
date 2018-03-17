cmake_minimum_required(VERSION 3.9)
project(PrettyTable CXX)

set(CMAKE_CXX_STANDARD 11)

include_directories(
        ./inc
        ./inc/table
        ./inc/utils
)

add_executable(
        PrettyTable
        src/main.cpp
)
