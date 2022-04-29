cmake_minimum_required(VERSION 3.21)
project(so_long C)

set(CMAKE_C_STANDARD 99)

include_directories(./mlx)
include_directories(./includes)

add_subdirectory(./mlx)

add_executable(so_long
        src/main.c
        src/utils.c
        src/get_next_line.c
        src/get_next_line_utils.c
        src/input.c
        src/game.c
        src/draw.c
        src/utils2.c
        src/mlx_init.c
        )

SET(CMAKE_C_FLAGS  " ${CMAKE_C_FLAGS} -Wall -Wextra")

target_link_libraries(so_long
        mlx
        "-framework OpenGL"
        "-framework AppKit")

