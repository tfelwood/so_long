/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfelwood <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 20:31:26 by tfelwood          #+#    #+#             */
/*   Updated: 2022/05/22 20:31:30 by tfelwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "../mlx/mlx.h"

static char	*ft_path_gen(const char *dir, int i, const char *ext)
{
	char	*str1;
	char	*str2;

	str1 = ft_itoa(i);
	if (!str1)
		return (NULL);
	str2 = ft_strjoin(dir, str1);
	free(str1);
	if (!str2)
		return (NULL);
	str1 = ft_strjoin(str2, ext);
	free(str2);
	return (str1);
}

static enum e_errors	ft_image_init(void *mlx_ptr,
			void **imgs, const char *dir, int size)
{
	int		i;
	char	*path;
	int		x;
	int		y;

	i = 0;
	while (i < size)
	{
		path = ft_path_gen(dir, i, EXT);
		if (!path)
			return (BAD_ALLOC);
		imgs[i] = mlx_xpm_file_to_image(mlx_ptr, path, &x, &y);
		free(path);
		if (!imgs[i])
			return (MLX_ERROR);
		++i;
	}
	return (NO_ERROR);
}

static void	ft_mlx_free_img(void *mlx_ptr, void **img_arr, int size)
{
	int	i;

	i = 0;
	while (i < size && img_arr[i])
	{
		mlx_destroy_image(mlx_ptr, img_arr[i]);
		++i;
	}
}

void	ft_mlx_free(struct s_game *sl)
{
	if (sl->mlx_ptr && sl->mlx_win_ptr)
	{
		mlx_destroy_window(sl->mlx_ptr, sl->mlx_win_ptr);
		ft_mlx_free_img(sl->mlx_ptr, sl->mlx_img, IMG_NUM);
		ft_mlx_free_img(sl->mlx_ptr, sl->spr_img, SPR_NUM);
	}
}

enum e_errors	ft_init_mlx(struct s_game *sl)
{
	int				width;
	int				height;
	enum e_errors	err;

	sl->mlx_ptr = mlx_init();
	if (!sl->mlx_ptr)
		return (MLX_ERROR);
	mlx_get_screen_size(&width, &height);
	if (IMG_SIZE * sl->map->length > width
		|| IMG_SIZE * sl->map->width > height)
		return (SCREEN_ERROR);
	sl->mlx_win_ptr = mlx_new_window(sl->mlx_ptr, sl->map->length * IMG_SIZE,
			sl->map->width * IMG_SIZE, GAME_NAME);
	if (!sl->mlx_win_ptr)
		return (MLX_ERROR);
	err = ft_image_init(sl->mlx_ptr, sl->spr_img, SPR_PATH, SPR_NUM);
	if (err == NO_ERROR)
		err = ft_image_init(sl->mlx_ptr, sl->mlx_img, IMG_PATH, IMG_NUM);
	return (err);
}
