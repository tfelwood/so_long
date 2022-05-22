/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cell.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfelwood <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 20:28:19 by tfelwood          #+#    #+#             */
/*   Updated: 2022/05/22 20:28:24 by tfelwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_cell	*ft_cell_init(t_cell *elem, t_cell *parent,
						const struct s_map *map, int pos)
{
	if (elem)
	{
		elem->pos = pos;
		elem->parent = parent;
		if (parent)
			elem->beg_way = parent->beg_way + 1;
		else
			elem->beg_way = 0;
		elem->all_way = elem->beg_way + ft_pos_dif(map, map->plr_pos, pos);
		elem->next = NULL;
	}
	return (elem);
}

t_cell	*ft_qu_new(const struct s_map *map, int pos, t_cell	*parent)
{
	t_cell	*elem;

	elem = (t_cell*) malloc(sizeof(t_cell));
	//printf("malloc %d\n", pos);
	return (ft_cell_init(elem, parent, map, pos));
}

