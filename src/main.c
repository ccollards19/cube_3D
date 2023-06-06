#include "../includes/cub3d.h"

void	set_values_to_null(t_game *game)
{
	game->mlx_ptr = NULL;
	game->win_ptr = NULL;
	game->file = NULL;
}

static void init_game(t_game *game, char *path)
{
	printf("game initialazing\n");
	game->file = get_file_array(path);
	printf(".\n");
	game->EA_path = get_path(game->file, EA);
	game->SO_path = get_path(game->file, SO);
	game->WE_path = get_path(game->file, WE);
	game->NO_path = get_path(game->file, NO);
	game->ceiling_color = get_color(game->file, CEILING);
	game->floor_color = get_color(game->file, FLOOR);
	game->map = get_map(game->file);
	game->down = 0;
	game->up = 0;
	game->left = 0;
	game->right = 0;
	game->should_cast = 1;
	game->mouse[0] = 0;
	game->mouse[1] = 0;
	game->hide_minimap = 0;
	printf("game initialized\n");
}

void	init_mlx(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (game->mlx_ptr == NULL)
		terminate(game, "");
	game->win_ptr = mlx_new_window(game->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Cube_3D");
	if (game->win_ptr == NULL)
		terminate(game, "");
	game->player = xmalloc(sizeof(t_player));
	game->player->angle = get_init_angle(game);
	set_player_position(game);
	game->frame.ptr = mlx_new_image(game->mlx_ptr, 1000, 1000);//test version
	game->frame.offset = mlx_get_data_addr(game->frame.ptr, &game->frame.bits_per_pixel, &game->frame.line_length, &game->frame.endian);//test version

	mlx_mouse_hide();
	mlx_mouse_move(game->win_ptr, 500, 500);
	mlx_mouse_get_pos(game->win_ptr, &game->mouse[0], &game->mouse[1]);
}

void init_asset(t_game *game)
{
	game->asset = xmalloc(sizeof(t_asset));
	if (game->asset == NULL)
		terminate(game, "");

	game->asset->NO.ptr = mlx_xpm_file_to_image(game->mlx_ptr, game->NO_path, &game->asset->NO.width, &game->asset->NO.height);
	if (game->asset->NO.ptr == NULL)
		terminate(game, "");
	game->asset->NO.offset = mlx_get_data_addr(game->asset->NO.ptr, &game->asset->NO.bits_per_pixel, &game->asset->NO.line_length, &game->asset->NO.endian);

	game->asset->SO.ptr = mlx_xpm_file_to_image(game->mlx_ptr, game->SO_path, &game->asset->SO.width, &game->asset->SO.height);
	if (game->asset->SO.ptr == NULL)
		terminate(game, "");
	game->asset->SO.offset = mlx_get_data_addr(game->asset->SO.ptr, &game->asset->SO.bits_per_pixel, &game->asset->SO.line_length, &game->asset->SO.endian);

	game->asset->WE.ptr = mlx_xpm_file_to_image(game->mlx_ptr, game->WE_path, &game->asset->WE.width, &game->asset->WE.height);
	if (game->asset->WE.ptr == NULL)
		terminate(game, "");
	game->asset->WE.offset = mlx_get_data_addr(game->asset->WE.ptr, &game->asset->WE.bits_per_pixel, &game->asset->WE.line_length, &game->asset->WE.endian);

	game->asset->EA.ptr = mlx_xpm_file_to_image(game->mlx_ptr, game->EA_path, &game->asset->EA.width, &(game->asset->EA.height));
	if (game->asset->EA.ptr == NULL)
		terminate(game, "");
	game->asset->EA.offset = mlx_get_data_addr(game->asset->EA.ptr, &game->asset->EA.bits_per_pixel, &game->asset->EA.line_length, &game->asset->EA.endian);
}

/*
void precompute(t_game *game)
{
	int i;
	double angle;

	i = 0;
	angle = 0;
	game->angle = malloc(sizeof(t_angle) * RAY_NBR);
	if (game->angle == NULL)
		terminate(game, "");
	while (i < RAY_NBR)
	{
		(game->angle)[i].angle = angle;
		(game->angle)[i].sin = sin(angle);
		(game->angle)[i].cos = cos(angle);
		(game->angle)[i].tan = tan(angle);
		(game->angle)[i].sin_inv = 1 / sin(angle);
		(game->angle)[i].cos_inv = 1 / cos(angle);

		angle += ((M_PI * 2) / RAY_NBR);
		i++;
	}
}
*/
int	main(int argc, char **argv)
{
	t_game game;

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
