//
// Created by Themis Felwood on 3/21/22.
//

#ifndef SO_LONG_H
# define SO_LONG_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "mlx.h"

# define WALL '1'
# define PLAYER 'P'
# define EXIT 'E'
# define COLLECTIBLE 'C'
# define SPACE '0'

enum	e_errors
{
	NO_ERROR,
	BAD_ARGS,
	BAD_DESCRIPTOR,
	BAD_FILE_FORMAT,
	MAP_BAD_FIGURE,
	MAP_BAD_ALPH,
	MAP_BAD_WALLS,
	MAP_BAD_PLAYER,
	MAP_BAD_EXIT,
	MAP_BAD_COLLECTIBLE,
};

struct	s_flags
{
	char	player;
	char	collectible;
	char	exit;
	char	is_wall;
};

struct	s_map
{
	size_t			width;
	size_t			length;
	struct s_flags	flags;
	char			*field;
};


void			ft_putstr_fd(const char *s, int fd);
size_t			ft_strlen(const char *str);
void			*ft_memset(void *b, int c, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
int				ft_strcmp(const char *s1, const char *s2);
enum e_errors	ft_input(int fd, struct s_map *map);
void			ft_init_game(struct s_map *map);
#endif
