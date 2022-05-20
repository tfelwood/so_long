/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfelwood <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 17:57:13 by tfelwood          #+#    #+#             */
/*   Updated: 2022/05/16 14:25:30 by tfelwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int ft_compare(t_cell *e1, t_cell *e2)
{
	return (!e2 || (e1 && e1->all_way < e2->all_way) || !(e1 || e2));
}

static int	ft_mod(long x)
{
	if (x < 0)
		return (-x);
	return (x);
}

int ft_pos_dif(const struct s_map *map, int pos1, int pos2)
{
	return (ft_mod(pos1 / map->length - pos2 / map->length) +
			ft_mod(pos1 % map->length - pos2 % map->length));
}

int	ft_is_obstacle(char c)
{
	return (c == WALL || c == ENEMY || c == COLLECTIBLE || c == EXIT);
}


t_cell *ft_qu_check(t_cell **lst, int key, int new_way)
{
	t_cell	*tmp;

	tmp = ft_qu_find(*lst, key);
	if (tmp && tmp->beg_way > new_way)
	{
		return (ft_qu_del(lst, key));
	}
	return (NULL);
}

/*OPEN = priority queue containing START
CLOSED = empty set
while lowest rank in OPEN is not the GOAL:
  current = remove lowest rank item from OPEN
  add current to CLOSED
  for neighbors of current:
    cost = g(current) + movementcost(current, neighbor)
    if neighbor in OPEN and cost less than g(neighbor):
      remove neighbor from OPEN, because new path is better
    if neighbor in CLOSED and cost less than g(neighbor): ⁽²⁾
      remove neighbor from CLOSED
    if neighbor not in OPEN and neighbor not in CLOSED:
      set g(neighbor) to cost
      add neighbor to OPEN
      set priority queue rank to g(neighbor) + h(neighbor)
      set neighbor's parent to current
reconstruct reverse path from goal to start
by following parent pointers*/


enum e_errors	ft_check_neighbours(struct s_game *sl, t_cell *elem,
		t_cell **open, t_cell **closed)
{
	int		i;
	t_cell	*tmp;

	const int pos[4] = {elem->pos + 1, elem->pos - 1, elem->pos +
						sl->map->length, elem->pos - sl->map->length};
	i = 0;
	while (i < 4)
	{
		if (!ft_is_obstacle(sl->map->field[pos[i]]))
		{
			tmp = ft_qu_check(open, pos[i], elem->beg_way + 1);
			if (!tmp)
				tmp = ft_qu_check(closed, pos[i], elem->beg_way + 1);
			if (tmp)
				ft_cell_init(tmp, elem, sl->map, pos[i]);
			else if (!ft_qu_find(*open, pos[i]) && !ft_qu_find(*closed, pos[i]))
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

enum e_errors	ft_a_star(struct s_game *sl, t_cell **open, t_cell **closed)
{
	t_cell			*cur;
	enum e_errors	err;

	err = NO_ERROR;
	while (*open)
	{
		cur = ft_qu_del(open, (*open)->pos);
		ft_lstadd_front(closed, cur);
		if (cur->pos == sl->map->cur_pl_pos)
			break;
		err = ft_check_neighbours(sl, cur, open, closed);
		if (err!= NO_ERROR)
			break;
	}
	return (err);
}

t_cell	*ft_form_path(t_cell *end, t_cell **lst)
{
	t_cell	*new_path;

	new_path  = NULL;
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
	open  = ft_qu_new(sl->map, sl->map->enm_pos, NULL);
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

int ft_enemy_move(struct s_game *sl)
{
	static int	count;
	t_cell		*elem;

	if (count == ENEMY_INTERVAL)
		count = 0;
	if (!count)
	{
		if (sl->map->cur_pl_pos != sl->map->plr_pos)
			ft_qu_free(&sl->enm_path);
		if (!sl->enm_path)
			sl->enm_path = ft_path_count(sl);
		sl->map->field[sl->map->enm_pos] = '0';
		sl->map->field[sl->enm_path->pos] = 'X';
		sl->map->enm_pos = sl->enm_path->pos;
		elem = sl->enm_path;
		sl->enm_path = sl->enm_path->next;
		free(elem);
	}
	++count;
	return (0);
}
