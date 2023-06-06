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
	int		i;
	int		len;

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
			print_element(&minimap, game, i, j);
	}
	print_player_fov(&minimap, game, trgb(128, 255, 255, 0));
	print_player(&minimap, 130, 130, trgb(128, 255, 100, 100));
	print_outer_circle(&minimap, 130, 65, white);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, minimap.ptr, 0, 0);
}
