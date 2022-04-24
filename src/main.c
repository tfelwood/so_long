#include "so_long.h"
#include <stdio.h>

//int main()
//{
//	void	*window;
//	void	*mlx_instance;
//	void	*mlx_image;
//	void	*mlx_image2;
//	void	*mlx_image3;
//	void	*mlx_image4;
//	int width;
//	int height;
//	int width2;
//	int height2;
//	int width3;
//	int height3;
//
//	mlx_instance = mlx_init();
//	window = mlx_new_window(mlx_instance, 1000, 1000, "Walhalla!");
//	mlx_image = mlx_xpm_file_to_image(mlx_instance, "./test_textures/water/100/0000.xpm", &width, &height);
//
//	mlx_image4 = mlx_xpm_file_to_image(mlx_instance, "./test_textures/fish3_100.xpm", &width3, &height3);
//	mlx_image3 = mlx_xpm_file_to_image(mlx_instance, "./test_textures/corals3100.xpm", &width2, &height2);
//	mlx_put_image_to_window(mlx_instance, window, mlx_image, 0, 0);
//	mlx_put_image_to_window(mlx_instance, window, mlx_image3, 0, 0);
////	mlx_put_image_to_window(mlx_instance, window, mlx_image2, width, 0);
//	mlx_put_image_to_window(mlx_instance, window, mlx_image, width, height);
//	mlx_put_image_to_window(mlx_instance, window, mlx_image, width, 0);
//	mlx_put_image_to_window(mlx_instance, window, mlx_image4, width, height);
//	mlx_put_image_to_window(mlx_instance, window, mlx_image3, width, 0);
//	//mlx_put_image_to_window(mlx_instance, window, mlx_image, width * 2, 0);
////	mlx_put_image_to_window(mlx_instance, window, mlx_image2, 0, height);
////	mlx_put_image_to_window(mlx_instance, window, mlx_image2, 0, height * 2);
//	printf("%d\n", width);
//	printf("%d\n", height);
//	mlx_loop(mlx_instance);
//	//mlx_destroy_image(mlx_instance, mlx_image);
//	//mlx_destroy_window(mlx_instance, window);
//	return 0;
//}

enum e_errors	ft_check_file_format(const char *filename)
{
	if (ft_strcmp(&filename[ft_strlen(filename) - 4], ".ber"))
		return (BAD_FILE_FORMAT);
	return (NO_ERROR);
}

int	ft_check_errors(enum e_errors err)
{
	static const char *errors[ERR_NUM] =
			{"Bad arguments\n","Сould not open the file\n",
			 "Bad file format\n","Map error: map must be rectangular\n",
			 "Map error: bad symbols\n",
			 "Map error: map must be surrounded by walls\n",
			 "Map error: no starting position or "
			 "more than one starting position\n",
			 "Map error: map must contain at least 1 exit\n",
			 "Map error: map must contain at least 1 collectible\n",
			 "Malloc error\n","File is empty\n","MLX error\n",
			 "The map size is larger than the screen size\n"};
	if (err == NO_ERROR)
		return (0);
	if (err < ERR_NUM)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(errors[err - 1], 2);
	}
	return (1);
}

void print(struct s_map *map)
{
	char	*tmp = map->field;
	int width = map->width;

	while (width--)
	{
		write(1, tmp, map->length);
		write(1, "\n", 1);
		tmp += map->length;
	}
}


static enum e_errors ft_parse_map(struct s_map *map, char *argv)
{

}


int main(int argc, char **argv)
{
	enum e_errors	error;
	int				fd;
	struct s_map	map;

	error = NO_ERROR;
	if (argc != 2)
		error = BAD_ARGS;
	else if (ft_check_file_format(argv[1]))
		error = BAD_FILE_FORMAT;
	if (!error)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			error = BAD_DESCRIPTOR;
		if (!error)
		{
			ft_memset(&map, 0, sizeof(map));
			error = ft_input(fd, &map);
			close(fd);
		}
	}
	if (ft_check_errors(error) || ft_check_errors(ft_init_game(&map)))
		free(map.field);
	//print(&map);
}
