#include "cub3d.h"

void	set_values_to_null(t_game *game)
{
	game->mlx_ptr = NULL;
	game->win_ptr = NULL;
	game->file = NULL;
}

static void init_game(t_game *game, char *path)
{
	game->file = get_file_array(path);
	int i = -1;
	while (game->file[++i])
		ft_printf("%d: %s\n", i, game->file[i]);
	game->EA_path = get_path(game->file, EA);
	game->SO_path = get_path(game->file, SO);
	game->WE_path = get_path(game->file, WE);
	game->NO_path = get_path(game->file, NO);
	game->ceiling_color = get_color(game->file, CEILING);
	game->floor_color = get_color(game->file, FLOOR);
	game->map = get_map(game->file);
}

void	init_mlx(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (game->mlx_ptr == NULL)
		terminate(game, "");
	game->win_ptr = mlx_new_window(game->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Cube_3D");//TODO macro must be defined
	if (game->win_ptr == NULL)
		terminate(game, "");
}

int	main(int argc, char **argv)
{
	t_game game;

	if (argc != 2)
		terminate(NULL, "invalid number of arguments\n");
	set_values_to_null(&game);
	init_game(&game, argv[1]);
	init_mlx(&game);
	game_loop(&game);
	return (0);
}
