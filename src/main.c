#include "so_long.h"


/*
int main()
{
	void	*window;
	void	*mlx_instance;
//	void	*mlx_image;
//	void	*mlx_image2;
//	int width;
//	int height;
//	int width2;
//	int height2;

	mlx_instance = mlx_init();
	window = mlx_new_window(mlx_instance, 92 * 3, 150, "Walhalla!");
//	mlx_image = mlx_xpm_file_to_image(mlx_instance, "delfin.xpm", &width, &height);
//	mlx_image2 = mlx_xpm_file_to_image(mlx_instance, "sand.xpm", &width2, &height2);
//	mlx_put_image_to_window(mlx_instance, window, mlx_image, 0, 0);
//	mlx_put_image_to_window(mlx_instance, window, mlx_image2, width, 0);
	//mlx_put_image_to_window(mlx_instance, window, mlx_image, width * 2, 0);
//	mlx_put_image_to_window(mlx_instance, window, mlx_image2, 0, height);
//	mlx_put_image_to_window(mlx_instance, window, mlx_image2, 0, height * 2);
//	printf("%d\n", width);
	mlx_loop(mlx_instance);
	//mlx_destroy_image(mlx_instance, mlx_image);
	//mlx_destroy_window(mlx_instance, window);
	return 0;
}
*/

enum e_errors	ft_check_file_format(const char *filename)
{
	if (ft_strcmp(&filename[ft_strlen(filename) - 4], ".ber"))
		return (BAD_FILE_FORMAT);
	return (NO_ERROR);
}

void	ft_check_errors(enum e_errors err)
{
	if (!err)
		return ;
	ft_putstr_fd("Error\n", 2);
	if (err == BAD_ARGS)
		ft_putstr_fd("Bad arguments\n",2);
	else if (err == BAD_DESCRIPTOR)
		ft_putstr_fd("Сould not open the file\n",2);
	else if (err == BAD_FILE_FORMAT)
		ft_putstr_fd("Bad file format\n",2);
	else if (err == MAP_BAD_FIGURE)
		ft_putstr_fd("Map error: map must be rectangular\n",2);
	else if (err == MAP_BAD_ALPH)
		ft_putstr_fd("Map error: bad symbols\n",2);
	else if (err == MAP_BAD_PLAYER)
		ft_putstr_fd("Map error: no starting position or "
					 "more than one tarting position\n",2);
	else if (err == MAP_BAD_WALLS)
		ft_putstr_fd("Map error: map must be surrounded by walls\n",2);
	else if (err == MAP_BAD_EXIT)
		ft_putstr_fd("Map error: map must contain at least 1 exit",2);
	else if (err == MAP_BAD_COLLECTIBLE)
		ft_putstr_fd("Map error: map must contain at least 1 collectible",2);
	exit(err);
}

int main(int argc, char **argv)
{
	enum e_errors	error;
	int				fd;
	struct s_map	map;

	error = NO_ERROR;
	ft_memset(&map, 0, sizeof(map));
	if (argc != 2)
		error = BAD_ARGS;
	error = ft_check_file_format(argv[1]);
	if (!error)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			error = BAD_DESCRIPTOR;
		if (!error)
		{
			error = ft_input(fd, &map);
			close(fd);
		}
	}
	if (error)
		free(map.field);
	ft_check_errors(error);
	ft_init_game(&map);
}
