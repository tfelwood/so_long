SRCS		=	main.c\
				get_next_line.c\
				get_next_line_utils.c\
				utils.c\
				input.c\
				game.c
OBJS		=	$(addprefix $(SOURCES),$(patsubst %.c,%.o,$(SRCS)))
NAME	 	=	so_long
LIB			=	mlx
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

$(LIB):
			make -C $(LIB)

$(NAME):	$(OBJS) $(LIB)
			$(CC) $(OBJS) $(FLAGS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

bonus:		all

-include	$(D_FILES)

clean:
		$(RM) $(OBJS)
		$(RM) $(D_FILES)

fclean:	clean
		${RM} $(NAME)

re:	fclean all
