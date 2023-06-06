#include "../includes/cub3d.h"

int	contain(char c, char *s)
{
	int	i;

	i = -1;
	if (c == '$')
	{
		while (s && s[++i])
		{
			if (s[i] == c && s[i + 1] != ' ')
				return (1);
		}
		return (0);
	}
	while (s && s[++i])
	{
		if (s[i] == c)
			return (1);
	}
	return (0);
}

int	trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

char	**get_map(char **file)
{
	char	**map;
	int	i;
	int	len;

	len = 1;
	i = 0;
	while (file[++i])
	{
		if (file[i][0] == '1')
			len++;
	}
	map = xmalloc(sizeof(char *) * len);
	len = 0;
	i = 0;
	while (file[++i])
	{
		if (file[i][0] == '1')
			map[len++] = file[i];
	}
	map[len] = NULL;
	i = 0;
	while (map[i])
		printf("%s\n", map[i++]);
	return (map);
}

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
		while (j < l && sqrt(((i - 130) * (i - 130)) + ((j - 130) * (j - 130))) <= 69)
			my_mlx_pixel_put(minimap, i, j++, color);
		i++;
	}
}
void	print_player(t_img *minimap, double i, double j, int color)
{
	int x;
	int y;
	int radius;

	radius = 3;
	x = (int)i - radius;
	while (x < (int)i + radius)
	{
		y = (int)j - radius;
		while (y < (int)j + radius)
		{
			if (sqrt(((i - x) * (i - x)) + ((j - y) * (j - y))) <= radius)
				my_mlx_pixel_put(minimap, x, y, color);
			y++;
		}
		x++;
	}

}

void	print_player_fov(t_img *minimap, t_game *game, int color)
{
	double angle;
	double delta[2];
	double point[2];
	double fov_demi;


	fov_demi = 0.8;
	angle = game->player->angle - fov_demi;
	while (angle < game->player->angle + fov_demi)
	{
		delta[0] = sin(angle) / 10;
		delta[1] = cos(angle) / 10;
		point[0] = game->player->x;
		point[1] = game->player->y;
		while(!is_wall(game->map, point[0], point[1]))
		{
			//printf("printing in [%d, %d]\n", (int)point[0], (int)point[1]);
			if (sqrt(((point[0] - game->player->x) * (point[0] - game->player->x)) + ((point[1] - game->player->y) * (point[1] - game->player->y))) <= 7)
				my_mlx_pixel_put(minimap, 130 - (int)((game->player->x - point[0]) * 10), 130 - (int)((game->player->y - point[1]) * 10), color);
			point[0] += delta[0];
			point[1] += delta[1];
		}
		angle += 0.005;
	}
}

void	print_outer_circle(t_img *img, int pos, int inner_radius, int color)
{
	int i;
	int j;
	double distance;

	i = 0;
	while(++i < pos * 3)
	{
		j = 0;
		while(++j < pos * 3)
		{
			distance = sqrt(((pos - i) * (pos - i)) + ((pos - j) * (pos - j)));
			if (distance > inner_radius && distance < inner_radius + 5) {
				//printf("yeah man\n");
				my_mlx_pixel_put(img, i, j, color);
			}
		}
	}
}

void clear(t_game *game)
{
	t_img	minimap;

	minimap.ptr = mlx_new_image(game->mlx_ptr, 1000, 1000);
	minimap.offset = mlx_get_data_addr(minimap.ptr, &minimap.bits_per_pixel, \
	&minimap.line_length, &minimap.endian);
	int i;
	int j;

	i = -1;
	while (++i < 1000)
	{
		j = -1;
		while (++j < 1000)
			my_mlx_pixel_put(&minimap, i, j, black);
	}
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,minimap.ptr, 0, 0);
}

void	minimap(t_game *game)
{
	t_img	minimap;
	int		i;
	int		j;

	i = -1;
	minimap.ptr = mlx_new_image(game->mlx_ptr, 1000, 1000);
	minimap.offset = mlx_get_data_addr(minimap.ptr, &minimap.bits_per_pixel, \
	&minimap.line_length, &minimap.endian);
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
		{
			if (sqrt(((i - game->player->x) * (i - game->player->x)) + ((j - game->player->y) * (j - game->player->y))) <= 7) {
				if (game->map[i][j] == '1')
					print_square(&minimap, 130 - (int)((game->player->x - i) * 10), 130 - (int)((game->player->y - j) * 10), trgb(128, 255, 255, 255));
				else
					print_square(&minimap, 130 - (int)((game->player->x - i) * 10), 130 - (int)((game->player->y - j) * 10), trgb(128, 0, 0, 0));
			}
		}
	}
	print_player_fov(&minimap, game, trgb(128, 255, 255, 0));
	print_player(&minimap, 130, 130, trgb(128, 255, 100, 100));
	print_outer_circle(&minimap, 130, 65, white);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,minimap.ptr, 0, 0);
}
