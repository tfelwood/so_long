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
	return (!ft_is_obstacle(sl->map->field[pos])
		&& ft_pos_dif(sl->map, pos, sl->map->plr_pos) > 2
		&& ft_path_count(sl));
}

int	ft_place_rand(struct s_game *sl,
					int (*cond)(int pos, struct s_game *sl))
{
	int 	count;
	char	*field;
	int 	pos;

	count = (sl->map->length - 2) * sl->map->width;
	field = (int *)malloc(count * sizeof(char));
	if (!field)
		ft_exit(sl, BAD_ALLOC);
	while (count--)
		field[count] = count + sl->map->length;
	count = (sl->map->length - 2) * sl->map->width;
	while (count)
	{
		pos = rand() % count;
		if (cond(field[pos + sl->map->length], sl))
			break;
		count--;
	}
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
		sl->map->field[pos] = 'X';
	else
		return (ENEMY_ERROR);
}


int ft_choose_move ();