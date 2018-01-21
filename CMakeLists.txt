cmake_minimum_required(VERSION 3.9)
project(tic_tac_toe C)

set(CMAKE_C_STANDARD 99)

add_executable(tic_tac_toe main.c tic_tac_toe.h board_drawing.c)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER})

target_link_libraries(tic_tac_toe ${GTK3_LIBRARIES})