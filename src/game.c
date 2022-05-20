//
// Created by Themis Felwood on 3/21/22.
//
#include "so_long.h"


/*static enum e_errors ft_image_init(struct s_game *sl)
{
	int 	i;
	int 	width;
	int 	height;

	static const char	*images[IMG_NUM] =
			{
			 "./test_textures/corals3100.xpm",
			 "./test_textures/fish3_100.xpm",
			 "./test_textures/n_d100.xpm",
			 "./test_textures/r100.xpm",
			 "./test_textures/angry_shark100.xpm"
			};
	i = 0;
	while (i < IMG_NUM)
	{
		sl->mlx_img[i] = mlx_xpm_file_to_image
				(sl->mlx_ptr, images[i], &width, &height);
		if (!sl->mlx_img[i])
			return (MLX_ERROR);
		++i;
	}
	return (NO_ERROR);
}*/



int	ft_exit(struct s_game *sl, enum e_errors err)
{
	ft_mlx_free(sl);
	free(sl->map->field);
	ft_check_errors(err);
	exit(0);
}

static void	ft_lose(struct s_game *sl)
{
	ft_putstr_fd("You lose! Movements: ", 1);
	ft_putnbr_fd(sl->move,1);
	ft_putstr_fd(" :(\n ", 1);
	ft_exit(sl, NO_ERROR);
}

static void	ft_win(struct s_game *sl)
{
	ft_putstr_fd("You win! Movements: ", 1);
	ft_putnbr_fd(sl->move,1);
	ft_putstr_fd(" :)\n ", 1);
	ft_exit(sl, NO_ERROR);
}

static void ft_move(struct s_game *sl, int new_pos)
{
	if (sl->map->field[new_pos] == WALL || (sl->map->field[new_pos] == EXIT
											&& sl->map->flags.collectible > 0))
		return ;
	++sl->move;
	if (sl->map->field[new_pos] == EXIT && !sl->map->flags.collectible)
	{
		ft_put_img(sl, sl->mlx_img[PLAYER_IM], new_pos);
		sl->map->field[sl->map->plr_pos] = SPACE;
		ft_win(sl);
	}
	else if (sl->map->field[new_pos] == ENEMY)
	{
		sl->map->field[sl->map->enm_pos] = SPACE;
		sl->map->field[sl->map->plr_pos] = ENEMY;
		ft_lose(sl);
	}
	else if (sl->map->field[new_pos] == COLLECTIBLE)
		--sl->map->flags.collectible;
	sl->map->field[sl->map->plr_pos] = SPACE;
	sl->map->field[new_pos] = PLAYER;
	sl->map->plr_pos = new_pos;
	ft_putstr_fd("Moves: ", 1);
	ft_putnbr_fd(sl->move, 1);
	ft_putstr_fd("\n",1);
}


static int	ft_key_proc(int key, struct s_game *sl)
{
	if (key == ESC)
		ft_exit(sl, NO_ERROR);
	else if (key == KEY_W || key == UP_ARROW)
		ft_move(sl, sl->map->plr_pos - sl->map->length);
	else if (key == KEY_S || key == DOWN_ARROW)
		ft_move(sl, sl->map->plr_pos + sl->map->length);
	else if (key == KEY_A || key == L_ARROW)
		ft_move(sl, sl->map->plr_pos - 1);
	else if (key == KEY_D || key == R_ARROW)
		ft_move(sl, sl->map->plr_pos + 1);
}

void	ft_init_game(struct s_map *map)
{
	struct s_game	sl;
	enum e_errors	error;

	ft_memset(&sl, 0, sizeof(sl));
	sl.map = map;
	error = ft_init_mlx(&sl);
	srand(time(0));
	if (!error)
		error = ft_enemy_place(&sl);
	if (error != NO_ERROR)
		ft_exit (&sl, error);
	ft_draw(&sl);
	mlx_loop_hook(sl.mlx_ptr, ft_draw_sprites, &sl);
	mlx_loop_hook(sl.mlx_ptr, ft_enemy_move, &sl);
	mlx_hook(sl.mlx_win_ptr, 17, 0, ft_exit, &sl);
	mlx_hook(sl.mlx_win_ptr, 2, 0, ft_key_proc, &sl);
	mlx_loop(sl.mlx_ptr);
}