cmake_minimum_required(VERSION 3.20)
project(so_long C)

set(CMAKE_C_STANDARD 99)

add_library(mlx STATIC font.c font_2x2.c mlx_shaders.c mlx_new_window.m mlx_init_loop.m mlx_new_image.m mlx_xpm.c mlx_int_str_to_wordtab.c
            mlx_png.c mlx_mouse.m mlx_get_screen_size.m)

