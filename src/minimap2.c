#include "../includes/cub3d.h"

void	print_square(t_img *minimap, int i, int j, int color)
{
	int	k;
	int	l;
	int	base_j;

	base_j = j;
	k = i + 10;
	l = j + 10;
	while (i < k)
	{
		j = base_j;
		while (j < l && (((i - 130) * (i - 130)) + ((j - 130) * \
		(j - 130))) <= 70 * 70)
			my_mlx_pixel_put(minimap, i, j++, color);
		i++;
	}
}

void	print_player(t_img *minimap, double i, double j, int color)
{
	int	x;
	int	y;
	int	radius;

	radius = 3;
	x = (int)i - radius;
	while (x < (int)i + radius)
	{
		y = (int)j - radius;
		while (y < (int)j + radius)
		{
			if ((((i - x) * (i - x)) + ((j - y) * (j - y))) <= radius * radius)
				my_mlx_pixel_put(minimap, x, y, color);
			y++;
		}
		x++;
	}
}

void	print_player_fov(t_img *minimap, t_game *game, int color)
{
	double	angle;
	double	delta[2];
	double	p[2];
	double	fov_demi;

	fov_demi = 0.5;
	angle = game->player->angle - fov_demi;
	while (angle < game->player->angle + fov_demi)
	{
		delta[0] = cos(angle) / 100;
		delta[1] = sin(angle) / 100;
		p[0] = game->player->x;
		p[1] = game->player->y;
		while (!is_wall(game->map, p[0], p[1]))
		{
			if ((((p[0] - game->player->x) * (p[0] - game->player->x)) + \
			((p[1] - game->player->y) * (p[1] - game->player->y))) <= 49)
				my_mlx_pixel_put(minimap, 130 - (int)((game->player->x - p[0]) \
				* 10), 130 - (int)((game->player->y - p[1]) * 10), color);
			p[0] += delta[0];
			p[1] += delta[1];
		}
		angle += 0.005;
	}
}

void	print_outer_circle(t_img *img, int pos, int inner_radius, int color)
{
	int		i;
	int		j;
	double	distance;

	i = inner_radius - 5;
	while (++i < pos * 2)
	{
		j = inner_radius - 5;
		while (++j < pos * 2)
		{
			distance = (((pos - i) * (pos - i)) + ((pos - j) * (pos - j)));
			if (distance >= inner_radius * inner_radius && distance <= \
			(inner_radius + 5) * (inner_radius + 5))
				my_mlx_pixel_put(img, i, j, color);
		}
	}
}

void	print_element(t_img *minimap, t_game *game, int i, int j)
{
	if ((((i - game->player->x) * (i - game->player->x)) + \
	((j - game->player->y) * (j - game->player->y))) <= 49)
	{
		if (game->map[i][j] == '1')
			print_square(minimap, 130 - (int)((game->player->x - i) * \
			10), 130 - (int)((game->player->y - j) * 10), \
			trgb(128, 255, 255, 255));
		else
			print_square(minimap, 130 - (int)((game->player->x - i) * \
			10), 130 - (int)((game->player->y - j) * 10), \
			trgb(128, 0, 0, 0));
	}
}
