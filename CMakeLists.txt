cmake_minimum_required(VERSION 3.31)
project(colors_C_C_plus_plus C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(src)

add_executable(colors_C_C_plus_plus
        example/example.c
        src/colors.c
        colors.h)
