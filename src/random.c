/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfelwood <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 18:16:50 by tfelwood          #+#    #+#             */
/*   Updated: 2022/05/16 14:00:34 by tfelwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int ft_cond_with_path(int pos, struct  s_game *sl)
{
	t_cell *cell;

	sl->map->enm_pos = pos;
	cell = ft_path_count(sl);
	if (!ft_is_obstacle(sl->map->field[pos])
		&& ft_pos_dif(sl->map, pos, sl->map->plr_pos) > 4
		&& cell)
	{
		ft_qu_free(&cell);
		return (1);
	}
	ft_qu_free(&cell);
	return (0);
}

int	ft_place_rand(struct s_game *sl,
					int (*cond)(int pos, struct s_game *sl))
{
	int 	count;
	int		*field;
	int 	pos;

	count = (sl->map->length - 2) * sl->map->width;
	field = (int *)malloc(count * sizeof(int));
	if (!field)
		ft_exit(sl, BAD_ALLOC);
	while (count--)
		field[count] = count + sl->map->length;
	count = (sl->map->length - 2) * sl->map->width;
	while (count)
	{
		pos = rand() % count;
		if (cond(field[pos], sl))
			break;
		field[pos] = field[count - 1];
		count--;
	}
	pos = field[pos];
	if (!count)
		pos = -1;
	free(field);
	return (pos);
}

int	ft_enemy_place(struct s_game *sl)
{
	int	pos;

	pos = ft_place_rand(sl, ft_cond_with_path);
	if (pos != -1)
	{
		sl->map->field[pos] = 'X';
		sl->map->enm_pos = pos;
		return (NO_ERROR);
	}
	else
		return (ENEMY_ERROR);
}
