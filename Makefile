# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tfelwood <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/23 16:14:27 by tfelwood          #+#    #+#              #
#    Updated: 2022/05/23 16:14:33 by tfelwood         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	main.c\
				utils.c\
				utils2.c\
				input.c\
				mlx_init.c\
				game.c\
				draw.c\
				bool_func.c\
				game_events.c

SRCS_BONUS	=	bool_func_bonus.c\
				enemy_bonus.c\
				game_events_bonus.c\
				mlx_init_bonus.c\
				utils2_bonus.c\
				cell_bonus.c\
				enemy_utils_bonus.c\
				input_bonus.c\
				queue_bonus.c\
				utils_bonus.c\
                draw_bonus.c\
                game_bonus.c\
                main_bonus.c\
                random_bonus.c

SRCS_GNL	=	get_next_line.c\
				get_next_line_utils.c

SRCS_DIR	=	src/
BONUS_DIR	=	bonus/
GNL_DIR		=	get_next_line/

OBJS		=	$(addprefix $(SRCS_DIR),$(patsubst %.c,%.o,$(SRCS)))
OBJS_GNL	=	$(addprefix $(GNL_DIR),$(patsubst %.c,%.o,$(SRCS_GNL)))
OBJS_BONUS	=	$(addprefix $(BONUS_DIR),$(patsubst %.c,%.o,$(SRCS_BONUS)))

MLX_F		=	mlx_init_loop.m mlx_int_str_to_wordtab.c mlx_mouse.m \
              	mlx_new_image.m mlx_new_window.m \
              	mlx_png.c mlx_shaders.c mlx_xpm.c mlx_get_screen_size.m

MLX_HH		=	mlx_int.h mlx_new_window.h \
				mlx_opengl.h mlx_png.h mlx.h

MLX_DIR		=	mlx/
MLX_H		=	$(addprefix $(MLX_DIR), $(MLX_HH))
MLX			= 	$(addprefix $(MLX_DIR), libmlx.a)
MLX_FLS		=	$(addprefix $(MLX_DIR), $(MLX_F))

D_FILES		=	$(addprefix $(SRCS_DIR),$(patsubst %.c,%.d,$(SRCS)))\
				+ $(addprefix $(BONUS_DIR),$(patsubst %.c,%.d,$(SRCS_BONUS)))\
				+ $(addprefix $(GNL_DIR),$(patsubst %.c,%.d,$(SRCS_GNL)))

NAME	 	=	so_long
NAME_BONUS	=	so_long_bonus
CC			= 	gcc
RM			=	rm -f
FLAGS		=	-Wall -Werror -Wextra

INCLUDES	=	includes

.PHONY:			all clean fclean re bonus

%.o:			%.c
				${CC} ${FLAGS} -I $(INCLUDES) -c $< -o ${<:.c=.o} -MMD

all:			$(NAME)

$(MLX):			$(MLX_H) $(MLX_FLS)
				make -C $(MLX_DIR)

$(NAME):		$(MLX) $(OBJS) $(OBJS_GNL)
				$(CC) $(OBJS) $(OBJS_GNL) $(FLAGS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

$(NAME_BONUS):	$(MLX) $(OBJS_BONUS) $(OBJS_GNL)
				$(CC) $(OBJS_BONUS) $(OBJS_GNL) $(FLAGS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME_BONUS)

bonus:			$(NAME_BONUS)

-include		$(D_FILES)

clean:
				$(RM) $(OBJS)
				$(RM) $(OBJS_GNL)
				$(RM) $(OBJS_BONUS)
				$(RM) $(D_FILES)
				make -C $(MLX_DIR) clean

fclean:			clean
				$(RM) $(NAME)
				$(RM) $(NAME_BONUS)

re:				fclean all
