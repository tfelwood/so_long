

#include "so_long.h"
#include "get_next_line.h"

static int ft_map_symbol_check(char c)
{
	if (c == PLAYER || c == EXIT || c == WALL || c == COLLECTIBLE
		|| c == SPACE)
		return (1);
	return (0);
}

static void	ft_flags_proc(char c, int pos, struct s_map *map)
{
	if (c == PLAYER)
	{
		++map->flags.player;
		map->plr_pos = map->width * map->length + pos;
	}
	else if (c == EXIT)
		++map->flags.exit;
	else if (c == COLLECTIBLE)
		++map->flags.collectible;
	else if (c == SPACE)
		++map->flags.empty;
}

static enum e_errors	ft_check_input(struct s_map *map, char *str)
{
	int				i;
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
		if (ft_map_symbol_check(str[i]))
			ft_flags_proc(str[i], i, map);
		else
			err = MAP_BAD_ALPH;
		++i;
	}
	if (!err && i != map->length)
		err = MAP_BAD_FIGURE;
	else if (!err && str[i - 1] != WALL)
		err = MAP_BAD_WALLS;
	return (err);
}

static void	ft_check_flags(struct s_map *map, enum e_errors *error)
{
	if (*error == NO_ERROR)
	{
		if (!map->flags.exit)
			*error = MAP_BAD_EXIT;
		else if (!map->flags.collectible)
			*error = MAP_BAD_COLLECTIBLE;
		else if (map->flags.player != 1)
			*error = MAP_BAD_PLAYER;
		else if (!map->flags.is_wall)
			*error = MAP_BAD_WALLS;
	}
}

static enum e_errors	ft_first_input(int fd, struct s_map *map, char **line)
{
	enum e_errors	error;

	*line = get_next_line(fd);
	if (!*line)
		return (EMPTY_FILE);
	map->length = ft_strlen(*line);
	error = ft_check_input(map, *line);
	if (error == NO_ERROR && !map->flags.is_wall)
		error = MAP_BAD_WALLS;
	if (error)
		free(*line);
	return (error);
}

enum e_errors	ft_input(int fd, struct s_map *map)
{
	char			*cur_str;
	enum e_errors	error;
	char			*tmp;

	error = ft_first_input(fd, map, &cur_str);
	while (!error && cur_str)
	{
		tmp = map->field;
		map->field = ft_strjoin(map->field, cur_str);
		free (tmp);
		free (cur_str);
		if (map->field)
		{
			++map->width;
			cur_str = get_next_line(fd);
			error = ft_check_input(map, cur_str);
		}
		else
			return (BAD_ALLOC);
	}
	ft_check_flags(map, &error);
	return (error);
}