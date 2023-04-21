#include "cub3d.h"

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
	game->EA_path = get_path(game->file, EA);printf(".\n");
	game->SO_path = get_path(game->file, SO);printf(".\n");
	game->WE_path = get_path(game->file, WE);printf(".\n");
	game->NO_path = get_path(game->file, NO);printf(".\n");
	game->ceiling_color = get_color(game->file, CEILING);printf(".\n");
	game->floor_color = get_color(game->file, FLOOR);printf(".\n");
	game->map = get_map(game->file);
	printf("game initialzed\n");
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
	loop_hook(game);
}
/*
void init_asset(t_game *game)
{
	game->asset = malloc(sizeof(t_asset));
	if (game->asset == NULL)
		terminate(game, "");
	(game->asset).NO.ptr = mlx_xpm_file_to_image(game->mlx_ptr, game->NO_path, (game->asset).NO.width, (game->asset).NO.height);
	if ((game->asset).NO.ptr == NULL)
		terminate(game, "");
	(game->asset).SO.ptr = mlx_xpm_file_to_image(game->mlx_ptr, game->SO_path, (game->asset).SO.width, (game->asset).SO.height);
	if ((game->asset).SO.ptr == NULL)
		terminate(game, "");
	(game->asset).WE.ptr = mlx_xpm_file_to_image(game->mlx_ptr, game->WE_path, (game->asset).WE.width, (game->asset).WE.height);
	if ((game->asset).WE.ptr == NULL)
		terminate(game, "");
	(game->asset).EA.ptr = mlx_xpm_file_to_image(game->mlx_ptr, game->EA_path, (game->asset).EA.width, (game->asset).EA.height);
	if ((game->asset).EA.ptr == NULL)
		terminate(game, "");
}


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
//	init_asset;
//	minimap(&game);
/*	t_ray ray;
	game.player->angle = 2.354;
	game.player->x= 8.1;
	game.player->y= 4.6;
	build_frame(&ray, &game);
	mlx_loop(game.mlx_ptr);
	*/game_loop(&game);
	
	return (0);
}
//////////////////////////////////////////////////////////////
/*
   int main()
   {

   for (int i = 0; i < mapWidth; i++)
   {
   for (int j = 0; j < mapHeight; j++)
   printf("%d ", map[j][i]);
   printf("\n");

   }
   build_frame(&ray);
   return 0;

   }*/
