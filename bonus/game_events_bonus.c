/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_events_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfelwood <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:07:23 by tfelwood          #+#    #+#             */
/*   Updated: 2022/05/23 16:07:27 by tfelwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	ft_lose(struct s_game *sl)
{
	ft_putstr_fd("You lose! Movements: ", 1);
	ft_putnbr_fd(sl->move, 1);
	ft_putstr_fd(" :(\n", 1);
	ft_exit(sl, NO_ERROR);
}

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
	else if (sl->map->field[new_pos] == ENEMY)
	{
		sl->map->field[sl->map->enm_pos] = SPACE;
		sl->map->field[sl->map->plr_pos] = ENEMY;
		ft_lose(sl);
	}
	else if (sl->map->field[new_pos] == COLLECTIBLE)
		--sl->map->flags.collectible;
	sl->map->field[sl->map->plr_pos] = SPACE;
	sl->map->field[new_pos] = PLAYER;
	sl->map->plr_pos = new_pos;
}

int	ft_enemy_move(struct s_game *sl)
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
		if (sl->enm_path->pos == sl->map->plr_pos)
			ft_lose(sl);
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
