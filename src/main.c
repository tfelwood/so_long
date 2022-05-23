/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfelwood <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 20:31:08 by tfelwood          #+#    #+#             */
/*   Updated: 2022/05/22 20:31:10 by tfelwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static enum e_errors	ft_check_file_format(const char *filename)
{
	if (ft_strcmp(&filename[ft_strlen(filename) - 4], ".ber"))
		return (BAD_FILE_FORMAT);
	return (NO_ERROR);
}

int	ft_check_errors(enum e_errors err)
{
	static const char	*errors[ERR_NUM] =
			{"Bad arguments\n", "Сould not open the file\n",
				"Bad file format\n", "Map error: map must be rectangular\n",
			"Map error: bad symbols\n",
			"Map error: map must be surrounded by walls\n",
			"Map error: no starting position or "
				"more than one starting position\n",
			"Map error: map must contain at least 1 exit\n",
			"Map error: map must contain at least 1 collectible\n",
			"Malloc error\n", "File is empty\n", "MLX error\n",
			"The map size is larger than the screen size\n"};

	if (err == NO_ERROR)
		return (0);
	if (err > NO_ERROR && err < ERR_NUM)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(errors[err - 1], 2);
	}
	return (1);
}

static enum e_errors	ft_read(char *path, struct s_map *map)
{
	int				fd;
	char			*tmp;
	enum e_errors	err;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (BAD_ALLOC);
	fd = open(tmp, O_RDONLY);
	free (tmp);
	if (fd != -1)
	{
		close(fd);
		return (BAD_DESCRIPTOR);
	}
	fd = open(path, O_RDONLY);
	if (fd > 0)
	{
		ft_memset(map, 0, sizeof(*map));
		err = ft_input(fd, map);
		close(fd);
	}
	else
		err = BAD_DESCRIPTOR;
	return (err);
}

int	main(int argc, char **argv)
{
	enum e_errors	error;
	struct s_map	map;

	error = NO_ERROR;
	if (argc != 2)
		error = BAD_ARGS;
	else if (ft_check_file_format(argv[1]))
		error = BAD_FILE_FORMAT;
	if (error == NO_ERROR)
		error = ft_read(argv[1], &map);
	if (ft_check_errors(error))
		free(map.field);
	else
		ft_init_game(&map);
}
