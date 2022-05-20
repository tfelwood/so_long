//
// Created by Themis Felwood on 4/29/22.
//

#ifndef QUEUE_H
#define QUEUE_H

typedef struct s_cell
{
	int				pos;
	struct s_cell	*parent;
	int				beg_way;
	int 			all_way;
	struct s_cell	*next;
} t_cell;

void	ft_lstadd_front(t_cell **lst, t_cell *new);
t_cell	*ft_qu_new(const struct s_map *map, int pos, t_cell	*parent);
t_cell	*ft_qu_add(t_cell **q, t_cell *elem,
					 int (*compr)(t_cell *, t_cell *));
t_cell	*ft_qu_del(t_cell **q, int key);
t_cell	*ft_qu_find(t_cell *lst, int key);
void	ft_qu_free(t_cell **lst);
t_cell	*ft_cell_init(t_cell *el, t_cell *parent,
						const struct s_map *map, int pos);
t_cell			*ft_path_count(struct s_game *sl);
#endif
