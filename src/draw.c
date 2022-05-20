#include "so_long.h"

void	ft_put_img(struct s_game *sl, void *sprite, int pos)
{
	mlx_put_image_to_window(sl->mlx_ptr, sl->mlx_win_ptr,
							sprite,(pos % sl->map->length) * IMG_SIZE,
							(pos / sl->map->length) * IMG_SIZE);
}

enum e_errors	ft_moves_input(struct s_game *sl)//todo вывод moves в консоль в небонусной части
{
	char	*str_move;

	str_move = ft_itoa(sl->move);
	if (!str_move)
		return (BAD_ALLOC);
	mlx_string_put(sl->mlx_ptr, sl->mlx_win_ptr, 10, 10, 5, str_move);
	free (str_move);
	return (NO_ERROR);
}

 void	ft_draw(struct s_game *sl)
{
	int i;

	i = 0;
	while (sl->map->field[i])
	{
		ft_put_img(sl, sl->spr_img[sl->cur_sprite], i);
		if (sl->map->field[i] == WALL)
			ft_put_img(sl, sl->mlx_img[WALL_IM], i);
		else if (sl->map->field[i] == COLLECTIBLE)
			ft_put_img(sl, sl->mlx_img[COLL_IM], i);
		else if (sl->map->field[i] == PLAYER)
			ft_put_img(sl, sl->mlx_img[PLAYER_IM], i);
		else if (sl->map->field[i] == EXIT)
			ft_put_img(sl, sl->mlx_img[EXIT_IM], i);
		else if (sl->map->field[i] == ENEMY)
			ft_put_img(sl, sl->mlx_img[ENEMY_IM], i);
		++i;
	}
	if (ft_moves_input(sl) != NO_ERROR)
		ft_exit(sl, BAD_ALLOC);
}

void ft_draw_sprites(struct s_game *sl)
{
	static int	count = 0;

	if (count == INTERVAL)
		count = 0;
	if (!count)
	{
		++sl->cur_sprite;
		if (sl->cur_sprite == SPR_NUM)
			sl->cur_sprite = 0;
		ft_draw(sl);
	}
	count++;
}

