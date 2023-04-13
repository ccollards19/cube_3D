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
	loop_hook(game);
}


int	main(int argc, char **argv)
{
	t_game game;

	if (argc != 2)
		terminate(NULL, "invalid number of arguments\n");
	(void)argv;
	set_values_to_null(&game);
	init_game(&game, argv[1]);
	init_mlx(&game);
//	minimap(&game);
	/*t_ray ray;
	ray.texture_offset = 0;
	ray.x = 3.1;
	ray.y = 3.1;
	ray.x0 = 3.1;
	ray.y0 = 3.1;
	ray.angle = M_PI_2 / 2;
	ray.dx = sin(ray.angle);
	ray.dx_inv = 1 / sin(ray.angle);
	ray.dy = cos(ray.angle);
	ray.dy_inv = 1 / cos(ray.angle);
	build_frame(&ray, &game);*/
	//ray.angle += 0.1;
	//usleep(10000);
	//mlx_do_sync(game->mlx_ptr)
	game_loop(&game);

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
