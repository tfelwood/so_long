cmake_minimum_required(VERSION 3.20)
project(so_long C)

set(CMAKE_C_STANDARD 99)

include_directories(./mlx)
include_directories(./includes)

add_subdirectory(./mlx)

add_executable(so_long
        src/main.c
        src/utils.c
        get_next_line/get_next_line.c
        get_next_line/get_next_line_utils.c
        src/input.c
        src/game.c
        src/draw.c
        src/utils2.c
        src/mlx_init.c
        src/bool_func.c
        src/game_events.c)

add_executable(so_long_bonus
        bonus/bool_func_bonus.c
        bonus/cell_bonus.c
        bonus/draw_bonus.c
        bonus/enemy_bonus.c
        bonus/enemy_utils_bonus.c
        bonus/game_bonus.c
        bonus/game_events_bonus.c
        bonus/input_bonus.c
        bonus/main_bonus.c
        bonus/mlx_init_bonus.c
        bonus/queue_bonus.c
        bonus/random_bonus.c
        bonus/utils_bonus.c
        bonus/utils2_bonus.c
        get_next_line/get_next_line.c
        get_next_line/get_next_line_utils.c)

SET(CMAKE_C_FLAGS  " ${CMAKE_C_FLAGS} -Wall -Wextra")

target_link_libraries(so_long
        mlx
        "-framework OpenGL"
        "-framework AppKit")

target_link_libraries(so_long_bonus
        mlx
        "-framework OpenGL"
        "-framework AppKit")

