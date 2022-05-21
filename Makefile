SRCS		=	main.c\
				get_next_line.c\
				get_next_line_utils.c\
				utils.c\
				utils2.c\
				input.c\
				mlx_init.c\
				game.c\
				draw.c\
				enemy.c\
				random.c\
				queue.c\

MLX_F		= font.c font.xcf mlx_init_loop.m \
              mlx_int.h mlx_int_str_to_wordtab.c mlx_mouse.m \
              mlx_new_image.m mlx_new_window.h mlx_new_window.m \
              mlx_opengl.h mlx_opengl.m mlx_png.c \
              mlx_png.h mlx_rgb.c mlx_shaders.c \
              mlx_xpm.c mlx_get_screen_size.m
MLX_DIR		= mlx/
MLX_H		= $(addprefix $(MLX_DIR), mlx.h)
MLX			= $(addprefix $(MLX_DIR), libmlx.a)
MLX_FLS		= $(addprefix $(MLX_DIR), $(MLX_F))

OBJS		=	$(addprefix $(SOURCES),$(patsubst %.c,%.o,$(SRCS)))
NAME	 	=	so_long
#LIB			=	$(LIB_DIR)/libmlx.a
#LIB_DIR		=	mlx
CC			= 	gcc
RM			=	rm -f
FLAGS		=	-Wall -Werror -Wextra
SOURCES		=	src/
INCLUDES	=	includes
D_FILES		=	$(addprefix $(SOURCES),$(patsubst %.c,%.d,$(SRCS)))
.PHONY:	all clean fclean re bonus
%.o:	%.c
		${CC} ${FLAGS} -I $(INCLUDES) -c $< -o ${<:.c=.o} -MMD

all:	$(NAME)

$(MLX):		$(MLX_H) $(MLX_FLS)
			make -C $(MLX_DIR)

$(NAME):	$(OBJS) $(MLX)
			$(CC) $(OBJS) $(FLAGS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

bonus:		all

-include	$(D_FILES)

clean:
		$(RM) $(OBJS)
		$(RM) $(D_FILES)
		make -C $(MLX_DIR) clean

fclean:	clean
		${RM} $(NAME)

re:	fclean all
