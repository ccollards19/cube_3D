#include "../includes/cub3d.h"

void	set_values_to_null(t_game *game)
{
	game->mlx_ptr = NULL;
	game->win_ptr = NULL;
	game->file = NULL;
	game->asset = NULL;
	game->minimap.ptr = NULL;
	game->player = NULL;
	game->gun_effect[0].ptr = NULL;
	game->gun.ptr = NULL;
	game->gun_sprite.ptr = NULL;
	game->frame.ptr = NULL;
}

char	*get_path(char **file, t_path path)
{
	int	i;
	int	stop;

	stop = 0;
	i = 0;
	while (file[i])
	{
		((path == EA && !ft_strncmp(file[i], "EA", 2) && ++stop) || \
		(path == SO && !ft_strncmp(file[i], "SO", 2) && ++stop) || \
		(path == WE && !ft_strncmp(file[i], "WE", 2) && ++stop) || \
		(path == NO && !ft_strncmp(file[i], "NO", 2) && ++stop));
		if (stop)
			break ;
		i++;
	}
	(stop && (\
	(path == EA && i != 3) || (path == SO && i != 1) || \
	(path == WE && i != 2) || (path == NO && i != 0)) \
	&& stop--);
	if (!stop || ft_strlen(file[i]) < 4)
		terminate(NULL, "syntax of .cub not respected1\n");
	return (file[i] + 3);
}

int	destroy(t_game *game)
{
	terminate(game, "Window got closed\n");
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		terminate(NULL, "invalid number of arguments\n");
	(void)argv;
	set_values_to_null(&game);
	init_game(&game, argv[1]);
	init_mlx(&game);
	init_asset(&game);
	game_loop(&game);
	return (0);
}
