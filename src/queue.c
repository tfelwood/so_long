//
// Created by Themis Felwood on 4/18/22.
//

#include "so_long.h"

/*
void ft_cpy(char *dst, char *src, int size)
{
	if (dst && src)
	{
		while(size--)
			dst[size] = src[size];
	}
}

void swap(struct s_elem *data, unsigned int num1, unsigned int num2){
	struct s_elem	tmp;

	ft_cpy((char *)&tmp, (char *)&data[num1], sizeof(struct s_elem));
	ft_cpy((char *)&data[num1], (char *)&data[num2], sizeof(struct s_elem));
	ft_cpy((char *)&data[num2], (char *)&tmp, sizeof(struct s_elem));
}

int	entropy(struct s_elem *elem)
{
	return (elem->beg_way + elem->end_way);
}

static void	ft_fixUp(struct s_queue *q, unsigned int child) {
	child = child + 1;
	while (child != 1) {
		if (entropy(&q->data[child - 1]) <=
				entropy(&q->data[child / 2 - 1]))
			break;
		swap(q->data, child - 1, child / 2 - 1);
		child /= 2;
	}
}

static void	ft_fixDown(struct s_queue *q, unsigned int parent)
{
	unsigned int child;

	parent = parent + 1;
	while (parent << 1 <= q->size)
	{
		child = parent << 1;
		if (child + 1 <= q->size &&
			entropy(&q->data[child]) > entropy(&q->data[child - 1]))
			child = child + 1;
		if (entropy(&q->data[parent - 1]) > entropy(&q->data[child - 1]))
			break;
		swap(q->data, child - 1, parent - 1);
		parent = child;
	}
}*/

static int	ft_mod(long x)
{
	if (x < 0)
		return (-x);
	return (x);
}

static int ft_pos_dif(struct s_map *map, int pos1, int pos2)
{
	return (ft_mod(pos1 / map->length - pos2 / map->length) +
			ft_mod(pos1 % map->length - pos2 % map->length));
}

t_list	*ft_lstnew(const struct s_game *g, int pos, t_list	*parent)
{
	t_list	*elem;

	elem = malloc(sizeof(t_list));
	if (elem)
	{
		elem->pos = pos;
		elem->parent = parent;
		elem->beg_way = parent->beg_way + 1;
		elem->all_way = elem->beg_way + ft_pos_dif(g->map, g->map->plr_pos, pos);
	}
	return (elem);
}