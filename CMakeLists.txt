cmake_minimum_required(VERSION 3.16)
project(tieto)

if (MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
        -Wconversion
        -Wsign-conversion
        -Wshadow
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Wnull-dereference
        -Wdouble-promotion
    )
endif()

add_subdirectory(common)

add_subdirectory(apps/tietoc)