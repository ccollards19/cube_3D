#include "cub3d.h"

int	destroy(t_game *game)
{
	//mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	terminate(game, "Window got closed\n");
	return (1);
}

void	get_ratio(double angle, double *x, double *y)
{
	double	x2;

	x2 = sin(angle);
	if (angle < M_PI_2)
	{
		*x = x2 - *y;
	}
	if (angle < 2 * M_PI_2)
	{
		*x = x2;
	}
	if (angle < 3 * M_PI_2)
	{
		*x = x2;
	}
	else
	{
		*x = 1 - x2;
	}
}

int	key_hook(int keycode, t_game *game)
{
	(void)game;
	double x;
	double y;
	get_ratio(game->player->angle, &x, &y);
	if (keycode == ESC)
		destroy(game);
	if (keycode == LEFT || keycode == A)
		game->player->x += 0.1;
	if (keycode == RIGHT || keycode == D)
		game->player->x -= 0.1;
	if (keycode == UP || keycode == W)
		game->player->y += 0.1;
	if (keycode == DOWN || keycode == S)
		game->player->y -= 0.1;
	printf("keycode is %d\n", keycode);
	printf("player position is [%f, %f]\n", game->player->x,game->player->y);
	return (0);
}

int	loop_hook(t_game *game)
{
	static int	previous_mouse_position[2];
	int 		current_mouse_position[2];
	static int once;

	if (!once++)
	{
		mlx_mouse_hide();
		mlx_mouse_get_pos(game->win_ptr, &previous_mouse_position[0], &previous_mouse_position[1]);
		return (19);
	}
	//printf("in loop_hook\n");
	mlx_mouse_get_pos(game->win_ptr, &current_mouse_position[0], &current_mouse_position[1]);
	//printf("1mouse position = %d %d\n", current_mouse_position[0], current_mouse_position[1]);
	if (current_mouse_position[0] > previous_mouse_position[0])
		game->player->angle += 0.05;
	if (current_mouse_position[0] < previous_mouse_position[0])
		game->player->angle -= 0.05;
	if (game->player->angle > PI2)
		game->player->angle -= PI2;
	if  (game->player->angle < 0)
		game->player->angle += PI2;
	if (current_mouse_position[0] < 0)
		mlx_mouse_move(game->win_ptr, 500, 0);
	if (current_mouse_position[0] > 1000)
		mlx_mouse_move(game->win_ptr, -500, 0);
	mlx_mouse_get_pos(game->win_ptr, &current_mouse_position[0], &current_mouse_position[1]);
	//printf("2mouse position = %d %d\ncurrent angle %f\n", current_mouse_position[0], current_mouse_position[1], game->player->angle);
	previous_mouse_position[0] = current_mouse_position[0];
	previous_mouse_position[1] = current_mouse_position[1];
	t_ray ray;
	ray.texture_offset = 0;
	ray.x = game->player->x;
	ray.y = game->player->y;
	ray.x0 = game->player->x;
	ray.y0 = game->player->y;
	ray.angle = game->player->angle;
	ray.dx = sin(ray.angle);
	ray.dx_inv = 1 / sin(ray.angle);
	ray.dy = cos(ray.angle);
	ray.dy_inv = 1 / cos(ray.angle);
	build_frame(&ray, game);
	return (0);
}
void	game_loop(t_game *game)
{
	mlx_hook(game->win_ptr, 17, 0, destroy, game);
	mlx_hook(game->win_ptr, 2, 0, key_hook, game);
	mlx_loop_hook(game->mlx_ptr, loop_hook, game);
	mlx_loop(game->mlx_ptr);

}
