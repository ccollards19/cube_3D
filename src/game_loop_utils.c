#include "../includes/cub3d.h"

int	handle_mouse(t_game *game)
{
	int	mouse[2];

	mlx_mouse_get_pos(game->win_ptr, &mouse[0], &mouse[1]);
	if (mouse[0] > game->mouse[0])
		game->player->angle += 0.1;
	else if (mouse[0] < game->mouse[0])
		game->player->angle -= 0.1;
	else
		return (0);
	if (game->player->angle > M_PI * 2)
		game->player->angle -= M_PI * 2;
	if (game->player->angle < 0)
		game->player->angle += M_PI * 2;
	mlx_mouse_move(game->win_ptr, 500, 500);
	mlx_mouse_get_pos(game->win_ptr, &game->mouse[0], &game->mouse[1]);
	return (1);
}

int	is_wall(char **map, double y, double x)
{
	int	i;
	int	j;

	i = (int)x;
	j = (int)y;
	if (map[j][i] == '1' || map[j][i] == ' ')
		return (1);
	else
		return (0);
}

void	raycast(t_game *game)
{
	t_ray	ray;

	ray.texture_offset = 0;
	ray.texture = 0;
	ray.x = game->player->x;
	ray.y = game->player->y;
	ray.x0 = game->player->x;
	ray.y0 = game->player->y;
	ray.angle = game->player->angle;
	if (!ray.angle || ray.angle == M_PI_2 || ray.angle == M_PI || ray.angle == (M_PI_2 * 3))
		ray.angle += 0.001;
	ray.dx = cos(ray.angle);
	ray.dx_inv = 1 / cos(ray.angle);
	ray.dy = sin(ray.angle);
	ray.dy_inv = 1 / sin(ray.angle);
	build_frame(&ray, game);
}

int	change_color(t_game *game)
{
	if (!game->color_change)
		return (0);
	game->color_type++;
	if (game->color_type == 1)
		game->ceiling_color = trgb(0, 0, 0, 255);
	else if (game->color_type == 2)
		game->ceiling_color = trgb(0, 255, 0, 0);
	else if (game->color_type == 3)
		game->ceiling_color = trgb(0, 0, 255, 0);
	else
		game->ceiling_color = get_color(game->file, CEILING);
	if (game->color_type == 1)
		game->floor_color = trgb(0, 0, 255, 0);
	else if (game->color_type == 2)
		game->floor_color = trgb(0, 0, 0, 255);
	else if (game->color_type == 3)
		game->floor_color = trgb(0, 255, 0, 0);
	else
		game->floor_color = get_color(game->file, FLOOR);
	if (game->color_type > 3)
		game->color_type = 0;
	return (1);
}

int	input_management(t_game *game, double d_x, double d_y)
{
	if (game->up || game->down)
	{
		d_x = cos(game->player->angle) / 10;
		d_y = sin(game->player->angle) / 10;
	}
	else if (!game->right && !game->left)
		return (0);
	if (game->up && !is_wall(game->map, game->player->x + \
	(d_x * 3), game->player->y + (d_y * 3)))
	{
		game->player->y += d_y;
		game->player->x += d_x;
	}
	if (game->down && !is_wall(game->map, game->player->x - \
	(d_x * 3), game->player->y - (d_y * 3)))
	{
		game->player->y -= d_y;
		game->player->x -= d_x;
	}
	if (game->left)
		game->player->angle += 0.05;
	if (game->right)
		game->player->angle -= 0.05;
	return (1);
}
