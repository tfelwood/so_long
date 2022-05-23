/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfelwood <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 20:30:14 by tfelwood          #+#    #+#             */
/*   Updated: 2022/05/22 20:30:17 by tfelwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_win(struct s_game *sl)
{
	ft_putstr_fd("You win! Movements: ", 1);
	ft_putnbr_fd(sl->move, 1);
	ft_putstr_fd(" :)\n", 1);
	ft_exit(sl, NO_ERROR);
}

void	ft_move(struct s_game *sl, int new_pos)
{
	if (sl->map->field[new_pos] == WALL || (sl->map->field[new_pos] == EXIT
			&& sl->map->flags.collectible > 0))
		return ;
	++sl->move;
	if (sl->map->field[new_pos] == EXIT && !sl->map->flags.collectible)
	{
		sl->map->field[sl->map->plr_pos] = SPACE;
		ft_win(sl);
	}
	else if (sl->map->field[new_pos] == COLLECTIBLE)
		--sl->map->flags.collectible;
	sl->map->field[sl->map->plr_pos] = SPACE;
	sl->map->field[new_pos] = PLAYER;
	sl->map->plr_pos = new_pos;
	ft_putstr_fd("Moves: ", 1);
	ft_putnbr_fd(sl->move, 1);
	ft_putstr_fd("\n", 1);
}
