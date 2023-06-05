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

	j *= 10;
	base_j = j;
	i *= 10;
	k = i + 10;
	l = j + 10;
	while (i < k)
	{
		j = base_j;
		while (j < l)
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
			if (sqrt((i - x) * (i - x)) + ((j - y) * (j - y)) <= radius)
				my_mlx_pixel_put(minimap, x, y, color);
			y++;
		}
		x++;
	}

}

void	print_player_fov(t_img *minimap, t_game *game, int color)
{
	double angle;
	double cosinus;
	double sinus;
	double point_b[2];

	angle = game->player->angle;
	sinus = sin(angle);
	cosinus = cos(angle);

	point_b[0] = game->player->x + 	3 * sinus;
	point_b[1] = game->player->y + 	3 * cosinus;
	print_player(minimap, point_b[0] * 10, point_b[1] * 10, color);
	//my_mlx_pixel_put(minimap, (int)point_b[0], (int)point_b[1], color);
}

void	minimap(t_game *game)
{
	t_img	minimap;
	int		i;
	int		j;

	i = -1;
	minimap.ptr = mlx_new_image(game->mlx_ptr, 400, 400);
	minimap.offset = mlx_get_data_addr(minimap.ptr, &minimap.bits_per_pixel, \
	&minimap.line_length, &minimap.endian);
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
		{
			if (game->map[i][j] == '1')
				print_square(&minimap, i, j, black);
			else
				print_square(&minimap, i, j, wheat);
		}
	}
	print_player(&minimap, game->player->x * 10, game->player->y * 10, blueviolet);
	print_player_fov(&minimap, game, light_yellow);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,minimap.ptr, 0, 0);
}
