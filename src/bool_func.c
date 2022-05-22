/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfelwood <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 20:27:40 by tfelwood          #+#    #+#             */
/*   Updated: 2022/05/22 20:27:51 by tfelwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int ft_map_symbol_check(char c)
{
	if (c == PLAYER || c == EXIT || c == WALL || c == COLLECTIBLE
		|| c == SPACE)
		return (1);
	return (0);
}

int	ft_is_obstacle(char c)
{
	return (c == WALL || c == ENEMY || c == COLLECTIBLE || c == EXIT);
}
