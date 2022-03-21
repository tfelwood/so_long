

#include "so_long.h"
#include "get_next_line.h"

static int ft_is_map_symbol(char c)
{
	if (c == PLAYER || c == EXIT || c == WALL || c == COLLECTIBLE
		|| c == SPACE)
		return (1);
	return (0);
}

static enum e_errors ft_check_input(struct s_map *map, char *str)
{
	size_t				i;
	enum e_errors	err;

	err = NO_ERROR;
	i = 0;
	if (!str)
		return (err);
	map->flags.is_wall = 1;
	if (str[i++] != WALL)
		err = MAP_BAD_WALLS;
	while (err == NO_ERROR && str[i] != '\0' && str[i] != '\n')
	{
		if (map->flags.is_wall && str[i] != WALL)
			map->flags.is_wall = 0;
		if (str[i] == PLAYER)
			++map->flags.player;
		if (!ft_is_map_symbol(str[i]))
			err = MAP_BAD_ALPH;
		++i;
	}
	if (i != map->length)
		err = MAP_BAD_FIGURE;
	else if (str[i - 1] != WALL)
		err = MAP_BAD_WALLS;
	return (err);
}

static void ft_check_flags(struct s_map *map, enum e_errors *error)
{
	if (!map->flags.collectible)
		*error = MAP_BAD_COLLECTIBLE;
	else if (!map->flags.exit)
		*error = MAP_BAD_EXIT;
	else if (map->flags.player != 1)
		*error =  MAP_BAD_PLAYER;
	else if (*error != MAP_BAD_FIGURE && !map->flags.is_wall)
		*error = MAP_BAD_WALLS;
}

enum e_errors	ft_input(int fd, struct s_map *map)
{
	char			*cur_str;
	enum e_errors	error;
	char			*tmp;

	error = NO_ERROR;
	cur_str = get_next_line(fd);
	map->length = ft_strlen(cur_str);
	if (cur_str)
		error = ft_check_input(map, cur_str);
	if (!error && !map->flags.is_wall)
		error = MAP_BAD_WALLS;
	while (!error && cur_str)
	{
		tmp = map->field;
		map->field = ft_strjoin(tmp, cur_str);
		free(tmp);
		free(cur_str);
		++map->width;
		cur_str = get_next_line(fd);
		error = ft_check_input(map, cur_str);
	}
	free(cur_str);
	ft_check_flags(map, &error);
	return (error);
}