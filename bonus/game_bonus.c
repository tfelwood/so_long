/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfelwood <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:07:03 by tfelwood          #+#    #+#             */
/*   Updated: 2022/05/23 16:07:13 by tfelwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "so_long_bonus.h"

int	ft_exit(struct s_game *sl, enum e_errors err)
{
	ft_mlx_free(sl);
	free(sl->map->field);
	ft_qu_free(&sl->enm_path);
	ft_check_errors(err);
	exit(0);
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
	return (0);
}

void	ft_init_game(struct s_map *map)
{
	struct s_game	sl;
	enum e_errors	error;

	ft_memset(&sl, 0, sizeof(sl));
	sl.map = map;
	error = ft_init_mlx(&sl);
	srand(time(0));
	if (error == NO_ERROR)
		error = ft_enemy_place(&sl);
	if (error != NO_ERROR)
		ft_exit (&sl, error);
	mlx_loop_hook(sl.mlx_ptr, ft_draw_sprites, &sl);
	mlx_hook(sl.mlx_win_ptr, 17, 0, ft_exit, &sl);
	mlx_hook(sl.mlx_win_ptr, 2, 0, ft_key_proc, &sl);
	mlx_loop(sl.mlx_ptr);
}
