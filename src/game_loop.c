#include "cub3d.h"

int	destroy(t_game *game)
{
	//mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	terminate(game, "Window got closed\n");
	return (1);
}
int	set_xy(double *x, double *y, double v_x, double v_y)
{
	printf("mooving...\n");
	*x += v_x;
	*y += v_y;
	return (1);
}

int is_inside_wall(t_game *game, double y, double x)
{
	char target;

	printf("x = %f y = %f\n", x, y);
	printf("rounded to [%d] [%d] = %c\n",(int)x, (int)y,game->map[(int)x][(int)y]);
	target = game->map[(int)x][(int)y];
	return (target == '1');
}

void	get_ratio(t_game *game, double orient)
{
	double	a;
	double	b;
	double	angle;
	static int t;

	printf("test %d\n", t++);
	angle = game->player->angle + orient;
	if (angle > PI2)
		angle -= PI2;
	(void)orient;
	b = game->player->sin;
	a = game->player->cos;
	if (game->player->angle < M_PI && game->player->angle >= 0)
		b = -b;
	printf("angle:\t%f\nsin:\t%f\ncos:\t%f\n", game->player->angle * M_PI, b, a);
	if (!is_inside_wall(game, game->player->y + a, game->player->x + b))
		set_xy(&game->player->x, &game->player->y, b, a);
	else
	{
		int new_x = (int)(game->player->x + 1);
		int new_y = (int)(game->player->y + 1);

		game->player->x = (double)new_x - 0.001;
		game->player->y = (double)new_y - 0.001;
	}
}
int	on_relase(int keycode, t_game *game)
{
	(void)keycode;
	printf("released\n");
	game->player->direction = NONE;
	return (0);
}

int	key_hook(int keycode, t_game *game)
{
	//printf("angle = %f\n", game->player->angle);
	//printf("BEFORE player position is [%f, %f]\n", game->player->x,game->player->y);
	if (keycode == ESC)
		destroy(game);
	if (keycode == LEFT || keycode == A)
		game->player->direction = WEST;
	if (keycode == RIGHT || keycode == D)
		game->player->direction = EAST;
	if (keycode == UP || keycode == W)
		game->player->direction = NORTH;
	if (keycode == DOWN || keycode == S)
		game->player->direction = SOUTH;
	printf("keycode is %d\n", keycode);
	//printf("AFTER player position is [%f, %f]\n", game->player->x,game->player->y);
	return (0);
}

int	loop_hook(t_game *game)
{
	static int	previous_mouse_position[2];
	int 		current_mouse_position[2];
	static int once;
	static t_ray ray;
	static double angle;

	mlx_mouse_hide();
	if (!once++)
	{
		angle = game->player->angle;
		game->player->sin = sin(angle) / 24;
		game->player->cos = cos(angle) / 24;
		mlx_mouse_get_pos(game->win_ptr, &previous_mouse_position[0], &previous_mouse_position[1]);
		game->player->direction = NONE;
		return (19);
	}
	if (game->player->direction != NONE)
		get_ratio(game, game->player->direction);
	mlx_mouse_get_pos(game->win_ptr, &current_mouse_position[0], &current_mouse_position[1]);
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
	if (current_mouse_position[1] < 100)
		mlx_mouse_move(game->win_ptr, 0, 400);
	if (current_mouse_position[1] > 900)
		mlx_mouse_move(game->win_ptr, 0, -400);
	mlx_mouse_get_pos(game->win_ptr, &current_mouse_position[0], &current_mouse_position[1]);
	if (game->player->angle != angle)
	{
		angle = game->player->angle;
		game->player->sin = sin(angle) / 24;
		game->player->cos = cos(angle) / 24;
	}
	//printf("2mouse position = %d %d\ncurrent angle %f\n", current_mouse_position[0], current_mouse_position[1], game->player->angle);
	previous_mouse_position[0] = current_mouse_position[0];
	previous_mouse_position[1] = current_mouse_position[1];

	ray.texture_offset = 0;
	ray.x = game->player->x;
	ray.y = game->player->y;
	ray.x0 = game->player->x;
	ray.y0 = game->player->y;
	if (game->player->direction != NONE || game->player->angle != ray.angle)
	{
		printf("rayrender\n");
		ray.angle = game->player->angle;
		ray.dx = sin(ray.angle);
		ray.dx_inv = 1 / sin(ray.angle);
		ray.dy = cos(ray.angle);
		ray.dy_inv = 1 / cos(ray.angle);
		build_frame(&ray, game);
	}

	//mlx_string_put(game->mlx_ptr, game->win_ptr, 10, 40, 0, ft_strjoin("current chunk: ", ft_itoa((int)(game->player->x))));
	//mlx_string_put(game->mlx_ptr, game->win_ptr, 130, 40, 0, ft_itoa((int)(game->player->y)));
	//mlx_string_put(game->mlx_ptr, game->win_ptr, 10, 10, 0, ft_strjoin("angle ", ft_itoa((int)(game->player->angle/ M_PI * 180))));
	return (0);
}
void	game_loop(t_game *game)
{
	mlx_hook(game->win_ptr, 17, 0, destroy, game);
	mlx_hook(game->win_ptr, 3, 1, on_relase, game);
	mlx_hook(game->win_ptr, 2, 0, key_hook, game);
	mlx_loop_hook(game->mlx_ptr, loop_hook, game);
	mlx_loop(game->mlx_ptr);

}
