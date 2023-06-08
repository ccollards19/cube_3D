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
	int		i[3];

	i[1] = 1;
	i[0] = 0;
	while (file[++i[0]])
	{
		i[2] = 0;
		while (file[i[0]][i[2]] == ' ' || file[i[1]][i[2]] == '\t')
			i[2]++;
		i[1] += (file[i[0]][i[2]] == '1');
	}
	map = xmalloc(sizeof(char *) * i[1]);
	i[1] = 0;
	i[0] = 0;
	while (file[++i[0]])
	{
		i[2] = 0;
		while (file[i[0]][i[2]] == ' ' || file[i[0]][i[2]] == '\t')
			i[2]++;
		if (file[i[0]][i[2]] == '1')
			map[i[1]++] = file[i[0]];
	}
	map[i[1]] = 0;
	return (map);
}

/*
 * Assign every pixel of the image to transparent
 * Then for each element of the map, print if it's nearby the player
 * the element is a square semi transparent, cut at the edges to fit in a circle
 * Then print the field of view noearby the player
 * Then print the player at the center of the minimap as a dot
 * Then print the image in the window
 */
void	minimap(t_game *game)
{
	t_img	minimap;
	int		i;
	int		j;

	i = -1;
	minimap = game->minimap;
	while (++i < 300)
	{
		j = -1;
		while (++j < 300)
			my_mlx_pixel_put(&minimap, i, j, trgb(255, 0, 0, 0));
	}
	i = -1;
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
