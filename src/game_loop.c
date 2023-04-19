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
	printf("rouned to [%d] [%d] = %c\n",(int)x, (int)y,game->map[(int)x][(int)y]);
	target = game->map[(int)x][(int)y];
	return (target == '1');
}

void	get_ratio(t_game *game, double orient)
{
	double	a;
	double	b;
	double	angle;

	angle = game->player->angle + orient;
	if (angle > PI2)
		angle -= PI2;
	(void)orient;
	b = sin(game->player->angle);
	a = cos(game->player->angle);
	if (game->player->angle < M_PI && game->player->angle >= 0 && \
	printf("hemisphere haut"))
		b = -b / 3;
	else if (printf("hemisphere bas"))
		b = b / 3;
	if ((game->player->angle > (M_3_PI_2) || game->player->angle < M_PI_2) && \
	printf(" droit\n"))
		a = a / 3;
	else if (printf(" gauche\n"))
		a = a / 3;
	printf("angle:\t%f\nsin:\t%f\ncos:\t%f\n", game->player->angle * M_PI, b, a);
	if (!is_inside_wall(game, game->player->y + a, game->player->x + b))
		set_xy(&game->player->x, &game->player->y, b, a);
	else if (orient != NORTH)
		set_xy(&game->player->x, &game->player->y, b, a);
}

int	key_hook(int keycode, t_game *game)
{
	//printf("angle = %f\n", game->player->angle);
	//printf("BEFORE player position is [%f, %f]\n", game->player->x,game->player->y);
	if (keycode == ESC)
		destroy(game);
	if (keycode == LEFT || keycode == A)
		get_ratio(game, WEST);
	if (keycode == RIGHT || keycode == D)
		get_ratio(game, EAST);
	if (keycode == UP || keycode == W)
		get_ratio(game, NORTH);
	if (keycode == DOWN || keycode == S)
		get_ratio(game, SOUTH);
	//printf("keycode is %d\n", keycode);
	//printf("AFTER player position is [%f, %f]\n", game->player->x,game->player->y);
	return (0);
}

int	loop_hook(t_game *game)
{
	static int	previous_mouse_position[2];
	int 		current_mouse_position[2];
	static int once;

	mlx_mouse_hide();
	if (!once++)
	{

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
	if (current_mouse_position[1] < 100)
		mlx_mouse_move(game->win_ptr, 0, 400);
	if (current_mouse_position[1] > 900)
		mlx_mouse_move(game->win_ptr, 0, -400);
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
	mlx_string_put(game->mlx_ptr, game->win_ptr, 10, 40, 0, ft_strjoin("current chunk: ", ft_itoa((int)(game->player->x))));
	mlx_string_put(game->mlx_ptr, game->win_ptr, 130, 40, 0, ft_itoa((int)(game->player->y)));
	mlx_string_put(game->mlx_ptr, game->win_ptr, 10, 10, 0, ft_strjoin("angle ", ft_itoa((int)(game->player->angle/ M_PI * 180))));
	return (0);
}
void	game_loop(t_game *game)
{
	mlx_hook(game->win_ptr, 17, 0, destroy, game);
	mlx_hook(game->win_ptr, 2, 0, key_hook, game);
	mlx_loop_hook(game->mlx_ptr, loop_hook, game);
	mlx_loop(game->mlx_ptr);

}
