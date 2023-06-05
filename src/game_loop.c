#include "cub3d.h"

int	destroy(t_game *game)
{
	//mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	terminate(game, "Window got closed\n");
	return (1);
}

int key_hook(int key, t_game *game)
{
	if (key == 53)
		exit(1);
	game->should_cast = 1;
	printf("key=%d\n", key);
	if (key == W)
		game->up = 1;
	if (key == S)
		game->down = 1;
	if (key == A)
		game->left = 1;
	if (key == D)
		game->right = 1;
	return (0);
}

int relase_key_hook(int key, t_game *game)
{
	if (key == W)
		game->up = 0;
	if (key == S)
		game->down = 0;
	if (key == A)
		game->left = 0;
	if (key == D)
		game->right = 0;
	printf("release %d\n", key);
	return (0);
}

int	handle_mouse(t_game *game)
{
	int mouse[2];

	mlx_mouse_get_pos(game->win_ptr, &mouse[0], &mouse[1]);
	if (mouse[0] > game->mouse[0] && printf("incre\n"))
		game->player->angle += 0.05;
	else if (mouse[0] < game->mouse[0] && printf("decr"))
		game->player->angle -= 0.05;
	else
		return (0);
	if (game->player->angle > M_PI * 2)
		game->player->angle -= M_PI * 2;
	if  (game->player->angle < 0)
		game->player->angle += M_PI * 2;
	mlx_mouse_move(game->win_ptr, 500, 500);
	mlx_mouse_get_pos(game->mlx_ptr, &game->mouse[0], &game->mouse[1]);
	return (1);
}


int is_wall(char **map, double y, double x)
{
	int intX = (int)x;
	int intY = (int)y;

	if (map[intY][intX] == '1')
		return (1);
	else
		return (0);
}



void raycast(t_game *game)
{
	t_ray	ray;

	ray.texture_offset = 0;
	ray.texture = 0;
	ray.x = game->player->x;
	ray.y = game->player->y;
	ray.x0 = game->player->x;
	ray.y0 = game->player->y;
	ray.angle = game->player->angle;
	ray.dx = cos(ray.angle);
	ray.dx_inv = 1 / cos(ray.angle);
	ray.dy = sin(ray.angle);
	ray.dy_inv = 1 / sin(ray.angle);
	build_frame(&ray, game);
}

void	input_management(t_game *game)
{
	double	d_x;
	double	d_y;

	if (game->up || game->down)
	{
		d_x = sin(game->player->angle) / 5000;
		d_y = cos(game->player->angle) / 5000;
	}
	else if (!game->right && !game->left)
		return ;
	if (game->up && !is_wall(game->map, game->player->x - d_x, game->player->y  + d_y))
	{
		game->player->y += d_y;
		game->player->x -= d_x;
	}
	if (game->down && !is_wall(game->map, game->player->x + d_x, game->player->y - d_y))
	{
		game->player->y -= d_y;
		game->player->x += d_x;
	}
	if (game->left)
		game->player->angle -= 0.5;
	if (game->right)
		game->player->angle += 0.5;
}
int loop_hook(t_game *game)
{
	int mouse_moove;

	printf("2.0\n");
	input_management(game);
	printf("2\n");
	mouse_moove = handle_mouse(game);
	printf("2\n");
	if (mouse_moove || (game->should_cast && game->should_cast--))
	{
		printf("2\n");
		t_ray	ray;

		ray.texture_offset = 0;
		ray.texture = 0;
		ray.x = game->player->x;
		ray.y = game->player->y;
		ray.x0 = game->player->x;
		ray.y0 = game->player->y;
		ray.angle = game->player->angle;
		ray.dx = cos(ray.angle);
		ray.dx_inv = 1 / cos(ray.angle);
		ray.dy = sin(ray.angle);
		ray.dy_inv = 1 / sin(ray.angle);
		build_frame(&ray, game);
		printf("2.end\n");
	}
	return (0);
}

void	game_loop(t_game *game)
{
	mlx_hook(game->win_ptr, 17, 0, destroy, game);
	mlx_hook(game->win_ptr, 3, 1L<<0, relase_key_hook, game);
	mlx_hook(game->win_ptr, 2, 1L<<1, key_hook, game);
	mlx_loop_hook(game->mlx_ptr, loop_hook, game);
	mlx_loop(game->win_ptr);
}
