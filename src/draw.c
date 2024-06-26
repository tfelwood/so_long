/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfelwood <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 20:28:40 by tfelwood          #+#    #+#             */
/*   Updated: 2022/05/22 20:28:43 by tfelwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "../mlx/mlx.h"

static void	ft_put_img(struct s_game *sl, void *sprite, int pos)
{
	mlx_put_image_to_window(sl->mlx_ptr, sl->mlx_win_ptr,
		sprite, (pos % sl->map->length) * IMG_SIZE,
		(pos / sl->map->length) * IMG_SIZE);
}

static void	ft_draw(struct s_game *sl)
{
	int	i;

	i = 0;
	while (sl->map->field[i])
	{
		ft_put_img(sl, sl->spr_img[sl->cur_sprite], i);
		if (sl->map->field[i] == WALL)
			ft_put_img(sl, sl->mlx_img[WALL_IM], i);
		else if (sl->map->field[i] == COLLECTIBLE)
			ft_put_img(sl, sl->mlx_img[COLL_IM], i);
		else if (sl->map->field[i] == PLAYER)
			ft_put_img(sl, sl->mlx_img[PLAYER_IM], i);
		else if (sl->map->field[i] == EXIT)
			ft_put_img(sl, sl->mlx_img[EXIT_IM], i);
		++i;
	}
}

int	ft_draw_sprites(struct s_game *sl)
{
	static int	count = 0;

	if (count == INTERVAL)
		count = 0;
	if (!count)
	{
		++sl->cur_sprite;
		if (sl->cur_sprite == SPR_NUM)
			sl->cur_sprite = 0;
		ft_draw(sl);
	}
	count++;
	return (0);
}
