#include "../includes/cub3d.h"

static void	init_cub(t_cub *cub, char *path)
{
	cub->file = get_file_array(path);
	cub->EA_path = get_path(cub->file, EA);
	cub->SO_path = get_path(cub->file, SO);
	cub->WE_path = get_path(cub->file, WE);
	cub->NO_path = get_path(cub->file, NO);
	cub->ceiling_color = get_color(cub->file, CEILING);
	cub->floor_color = get_color(cub->file, FLOOR);
}

int main(int argc, char **argv)
{
	t_cub	cub;

	ft_printf("%d\n", 0x00FFFF);
	if (argc != 2)
		return (print_err(1, "Error: invalid number of arguments\n"));
	init_cub(&cub, argv[1]);
	void *mlx_ptr = mlx_init();
	void *win_ptr = mlx_new_window(mlx_ptr, 1000, 1000, "test");
	(void)win_ptr;
	mlx_loop(mlx_ptr);
	return (0);
}
