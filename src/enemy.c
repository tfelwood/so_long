//
// Created by Themis Felwood on 4/29/22.
//

#include "queue.h"

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

static int ft_pos_dif(const struct s_map *map, int pos1, int pos2)
{
	return (ft_mod(pos1 / map->length - pos2 / map->length) +
			ft_mod(pos1 % map->length - pos2 % map->length));
}

static int	ft_is_obstacle(char c)
{
	return (c == WALL || c == ENEMY || c == COLLECTIBLE || c == EXIT);
}


enum e_errors	ft_check_neighbours(struct s_game *sl, t_cell *elem,
		t_cell **open, t_cell **closed)
{
	int		i;
	t_cell	*tmp;

	const int pos[4] = {elem->pos + 1, elem->pos - 1,
						elem->pos + sl->map->length,
						elem->pos - sl->map->length};
	i = 0;
	while (i < 4)
	{
		tmp = NULL;
		if (!ft_is_obstacle(sl->map->field[pos[i]]))
		{
			if (ft_qu_find(*open, pos[i]) &&
			(ft_qu_find(*open, pos[i]))->beg_way > elem->beg_way + 1)
				tmp = ft_qu_del(*open, pos[i]);
			else if (ft_qu_find(*closed, pos[i]) &&
				(ft_qu_find(*closed, pos[i]))->beg_way > elem->beg_way + 1)
				tmp = ft_qu_del(*open, pos[i]);

			if (tmp)
			{
				tmp->beg_way = elem->beg_way + 1;
				tmp->all_way = elem->beg_way + 1 +
						ft_pos_dif(sl->map, i, sl->map->cur_pl_pos);
			}
			else if (!ft_qu_find(*open, pos[i])
				&& !ft_qu_find(*closed, pos[i]))
			{
				tmp = ft_qu_new(sl->map, i, elem);
				if (!tmp)
					return (BAD_ALLOC);
				ft_qu_add(open, tmp, ft_compare);
			}
		}
		++i;
	}
	return (NO_ERROR);
}

enum e_errors	ft_a_star(struct s_game *sl, t_cell **open, t_cell **closed)
{
	t_cell	*cur;

	while (*open)
	{
		cur = ft_qu_del(open, *open);
		ft_lstadd_front(closed, cur);
		if ()
	}
}

t_cell	*ft_form_path(t_cell *end, t_cell **lst)
{
	t_cell	*new_path;

	new_path  = NULL;
	while (end && end->parent != NULL)
	{
		ft_qu_del(lst, end);
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
	if (!open || !(ft_a_star(sl, &open, &closed)))
		ft_exit(sl, BAD_ALLOC);
	if (ft_qu_find(closed, sl->map->enm_pos))
		path = ft_form_path(ft_qu_find(closed, sl->map->cur_pl_pos), &closed);
	ft_qu_free(open);
	ft_qu_free(closed);
	return(path);
}
