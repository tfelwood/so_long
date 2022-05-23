/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfelwood <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:06:38 by tfelwood          #+#    #+#             */
/*   Updated: 2022/05/23 16:06:42 by tfelwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static t_cell	*ft_check_lists(t_cell **open,
		t_cell **closed, int pos, int way)
{
	t_cell	*tmp;

	tmp = ft_qu_check(open, pos, way);
	if (!tmp)
		tmp = ft_qu_check(closed, pos, way);
	return (tmp);
}

static enum e_errors	ft_check_neighbours(struct s_game *sl, t_cell *elem,
		t_cell **open, t_cell **closed)
{
	const int	pos[4] = {elem->pos + 1, elem->pos - 1, elem->pos +
			sl->map->length, elem->pos - sl->map->length};
	int			i;
	t_cell		*tmp;

	i = 0;
	while (i < 4)
	{
		if (!ft_is_obstacle(sl->map->field[pos[i]]))
		{
			tmp = ft_check_lists(open, closed, pos[i], elem->beg_way + 1);
			if (tmp)
				ft_cell_init(tmp, elem, sl->map, pos[i]);
			else if (!ft_qu_find(*open, pos[i])
				&& !ft_qu_find(*closed, pos[i]))
			{
				tmp = ft_qu_new(sl->map, pos[i], elem);
				if (!tmp)
					return (BAD_ALLOC);
			}
			ft_qu_add(open, tmp, ft_compare);
		}
		++i;
	}
	return (NO_ERROR);
}

static enum e_errors	ft_a_star(struct s_game *sl,
		t_cell **open, t_cell **closed)
{
	t_cell			*cur;
	enum e_errors	err;

	err = NO_ERROR;
	while (*open)
	{
		cur = ft_qu_del(open, (*open)->pos);
		ft_lstadd_front(closed, cur);
		if (cur->pos == sl->map->cur_pl_pos)
			break ;
		err = ft_check_neighbours(sl, cur, open, closed);
		if (err != NO_ERROR)
			break ;
	}
	return (err);
}

static t_cell	*ft_form_path(t_cell *end, t_cell **lst)
{
	t_cell	*new_path;

	new_path = NULL;
	while (end && end->parent != NULL)
	{
		ft_qu_del(lst, end->pos);
		ft_lstadd_front(&new_path, end);
		end = end->parent;
	}
	return (new_path);
}

t_cell	*ft_path_count(struct s_game *sl)
{
	t_cell	*open;
	t_cell	*closed;
	t_cell	*path;

	sl->map->cur_pl_pos = sl->map->plr_pos;
	closed = NULL;
	path = NULL;
	open = ft_qu_new(sl->map, sl->map->enm_pos, NULL);
	if (!open || (ft_a_star(sl, &open, &closed)) != NO_ERROR)
	{
		ft_qu_free(&open);
		ft_qu_free(&closed);
		ft_exit(sl, BAD_ALLOC);
	}
	if (ft_qu_find(closed, sl->map->cur_pl_pos))
		path = ft_form_path(ft_qu_find(closed, sl->map->cur_pl_pos), &closed);
	ft_qu_free(&open);
	ft_qu_free(&closed);
	return (path);
}
