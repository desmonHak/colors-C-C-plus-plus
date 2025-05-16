cmake_minimum_required(VERSION 3.28)
project(colors_C_C_plus_plus C)

set(CMAKE_C_STANDARD 11)

# Permitir establecer modo Debug o Release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# Configuraciones específicas por tipo de compilación
set(CMAKE_C_FLAGS_DEBUG "-DDEBUG_ENABLE -g -O0")
set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")

include_directories(.)
include_directories(src)

add_executable(example
        example/example.c
        src/colors.c
        colors.h)
