/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfelwood <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:06:47 by tfelwood          #+#    #+#             */
/*   Updated: 2022/05/23 16:06:52 by tfelwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	ft_compare(t_cell *e1, t_cell *e2)
{
	return (!e2 || (e1 && e1->all_way < e2->all_way) || !(e1 || e2));
}

static int	ft_mod(long x)
{
	if (x < 0)
		return (-x);
	return (x);
}

int	ft_pos_dif(const struct s_map *map, int pos1, int pos2)
{
	return (ft_mod(pos1 / map->length - pos2 / map->length)
		+ ft_mod(pos1 % map->length - pos2 % map->length));
}

t_cell	*ft_qu_check(t_cell **lst, int key, int new_way)
{
	t_cell	*tmp;

	tmp = ft_qu_find(*lst, key);
	if (tmp && tmp->beg_way > new_way)
	{
		return (ft_qu_del(lst, key));
	}
	return (NULL);
}
