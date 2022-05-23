/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfelwood <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:08:28 by tfelwood          #+#    #+#             */
/*   Updated: 2022/05/23 16:08:33 by tfelwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue_bonus.h"

void	ft_lstadd_front(t_cell **lst, t_cell *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}

t_cell	*ft_qu_add(t_cell **q, t_cell *elem,
			int (*comp)(t_cell *, t_cell *))
{
	t_cell	*prev;

	if (!elem)
		return (NULL);
	elem->next = NULL;
	if (!(*q))
		*q = elem;
	else if (comp(elem, *q))
	{
		elem->next = *q;
		*q = elem;
	}
	else
	{
		prev = *q;
		while (comp(prev->next, elem))
			prev = prev->next;
		elem->next = prev->next;
		prev->next = elem;
	}
	return (elem);
}

t_cell	*ft_qu_del(t_cell **q, int key)
{
	t_cell	*tmp;
	t_cell	*elem;

	tmp = *q;
	if (!tmp || key < 0)
		return (NULL);
	if (tmp->pos == key)
	{
		*q = (*q)->next;
		elem = tmp;
	}
	else
	{
		while (tmp->next && tmp->next->pos != key)
			tmp = tmp->next;
		if (!tmp->next)
			return (NULL);
		else
		{
			elem = tmp->next;
			tmp->next = tmp->next->next;
		}
	}
	elem->next = NULL;
	return (elem);
}

t_cell	*ft_qu_find(t_cell *lst, int key)
{
	while (lst)
	{
		if (lst->pos == key)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	ft_qu_free(t_cell **lst)
{
	t_cell	*tmp;

	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp);
	}
	*lst = NULL;
}
