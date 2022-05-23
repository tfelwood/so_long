/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfelwood <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 15:58:02 by tfelwood          #+#    #+#             */
/*   Updated: 2022/05/23 15:58:14 by tfelwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <time.h>
# include "queue_bonus.h"

# define WALL '1'
# define PLAYER 'P'
# define EXIT 'E'
# define COLLECTIBLE 'C'
# define SPACE '0'
# define ENEMY  'X'
# define ERR_NUM 15
# define IMG_NUM 5
# define SPR_NUM 40
# define GAME_NAME "so long"
# define IMG_SIZE  100
# define SPR_PATH "./test_textures/water/100/"
# define IMG_PATH "./test_textures/"
# define EXT ".xpm"
# define INTERVAL 10
# define ENEMY_INTERVAL 60

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
	ENEMY_ERROR,
	BAD_ALLOC,
	EMPTY_FILE,
	MLX_ERROR,
	SCREEN_ERROR,
};

enum	e_images
{
	WALL_IM,
	COLL_IM,
	PLAYER_IM,
	EXIT_IM,
	ENEMY_IM,
};

typedef enum e_keycodes
{
	ESC				= 0x35,
	L_ARROW			= 0x7B,
	R_ARROW			= 0x7C,
	DOWN_ARROW		= 0x7D,
	UP_ARROW		= 0x7E,
	KEY_W			= 0x0D,
	KEY_A			= 0x00,
	KEY_S			= 0x01,
	KEY_D			= 0x02,
}	t_keycodes;

struct	s_flags
{
	int		player;
	int		collectible;
	int		exit;
	char	is_wall;
};

struct	s_map
{
	int				width;
	int				length;
	struct s_flags	flags;
	char			*field;
	int				plr_pos;
	int				enm_pos;
	int				cur_pl_pos;
};

struct s_game
{
	struct s_map	*map;
	size_t			move;
	void			*mlx_ptr;
	void			*mlx_win_ptr;
	int				cur_sprite;
	void			*mlx_img[IMG_NUM];
	void			*spr_img[SPR_NUM];
	t_cell			*enm_path;
};

int				ft_map_symbol_check(char c);
t_cell			*ft_qu_check(t_cell **lst, int key, int new_way);
int				ft_compare(t_cell *e1, t_cell *e2);
void			ft_putstr_fd(const char *s, int fd);
int				ft_strlen(const char *str);
void			*ft_memset(void *b, int c, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_itoa(int n);
void			ft_putnbr_fd(int n, int fd);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_pos_dif(const struct s_map *map, int pos1, int pos2);
int				ft_check_errors(enum e_errors err);
enum e_errors	ft_input(int fd, struct s_map *map);
enum e_errors	ft_init_mlx(struct s_game *sl);
void			ft_mlx_free(struct s_game *sl);
int				ft_enemy_place(struct s_game *sl);
void			ft_init_game(struct s_map *map);
int				ft_exit(struct s_game *sl, enum e_errors err);
int				ft_draw_sprites(struct s_game *sl);
int				ft_is_obstacle(char c);
void			ft_move(struct s_game *sl, int new_pos);
int				ft_enemy_move(struct s_game *sl);
#endif
