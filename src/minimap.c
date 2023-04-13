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


void	minimap(t_game *game)
{
	//void	*minia;
	int i = -1;
	int j;
	//mlx_mouse_hide();
	//void* test = mlx_xpm_file_to_image(game->mlx_ptr, "transparent.xpm", &i, &j);
	//minia = mlx_new_image(game->mlx_ptr, WIN_HEIGHT/4, WIN_WIDTH/4);
	while (++i < WIN_HEIGHT/4)
	{
		j = -1;
		while (++j < WIN_WIDTH/4)
			mlx_pixel_put(game->mlx_ptr, game->mlx_ptr, i, j, light_gray);
	}
	//ft_printf("%s\n%p\n", test, test);
	//void* test2 = mlx_xpm_file_to_image(game->mlx_ptr, "spirou.xpm", &i, &j);
	//mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, minia, 10, 10);
}
