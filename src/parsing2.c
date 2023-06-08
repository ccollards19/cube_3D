#include "../includes/cub3d.h"

char	*add_spaces(char *line, size_t target_len)
{
	char	*tmp;
	size_t	i;

	i = -1;
	if (ft_strlen(line) < target_len)
	{
		tmp = xmalloc((int)target_len * sizeof(char));
		while (line[++i])
			tmp[i] = line[i];
		while (i < target_len)
			tmp[i++] = 32;
		tmp[i] = 0;
		return (tmp);
	}
	else
		return (ft_strdup(line));
}

void	fill_map_blanks(t_game *game, char **map)
{
	size_t	i;
	size_t	j;

	i = -1;
	j = 0;
	game->map_allocated = 1;
	while (map[++i])
	{
		if (!valid_map_line(map[i]))
		{
			map[i] = 0;
			terminate(game, "Invalid map\n");
		}
		if (ft_strlen(map[i]) > j)
			j = ft_strlen(map[i]);
	}
	i = -1;
	while (game->map[++i])
		game->map[i] = add_spaces(map[i], j);
}

int	closed_map(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '0')
			{
				if (i == 0 || map[i + 1] == 0 || j == 0 || map[i][j + 1] == 0)
					return (0);
				if (map[i + 1][j] == ' ' || map[i - 1][j] == ' ' || \
				map[i][j - 1] == ' ' || map[i][j + 1] == ' ')
					return (0);
			}
		}
	}
	return (1);
}

char	*get_path(char **file, t_path path)
{
	int	i;
	int	stop;

	stop = 0;
	i = 0;
	while (file[i])
	{
		((path == EA && !ft_strncmp(file[i], "EA", 2) && ++stop) || \
		(path == SO && !ft_strncmp(file[i], "SO", 2) && ++stop) || \
		(path == WE && !ft_strncmp(file[i], "WE", 2) && ++stop) || \
		(path == NO && !ft_strncmp(file[i], "NO", 2) && ++stop));
		if (stop)
			break ;
		i++;
	}
	(stop && (\
	(path == EA && i != 3) || (path == SO && i != 1) || \
	(path == WE && i != 2) || (path == NO && i != 0)) \
	&& stop--);
	if (!stop || ft_strlen(file[i]) < 4)
		terminate(NULL, "syntax of .cub not respected1\n");
	return (file[i] + 3);
}

int	is_hallway(char **map, int i, int j)
{
	return (i && map[i + 1] && j && map[i][j] == '0' && ((map[i + 1][j] == '0' && \
	map[i - 1][j] == '0' && map[i][j + 1] == '1' && map[i][j - 1] == '1') || \
	(map[i + 1][j] == '1' && map[i - 1][j] == '1' && map[i][j + 1] == '0' && \
	map[i][j - 1] == '0')));
}

void	add_doors(t_game *game, int i, int j)
{
	while (game->map[++i])
		printf("%s\n", game->map[i]);
	i = -1;
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
		{
			if (game->map[i][j] == 'S' || game->map[i][j] == 'W' || \
			game->map[i][j] == 'E' || game->map[i][j] == 'N')
				game->map[i][j] = '0';
			if (is_hallway(game->map, i, j) && \
			((!is_hallway(game->map, i - 1, j) && \
			!is_hallway(game->map, i + 1, j)) || \
			(!is_hallway(game->map, i, j -1) && \
			!is_hallway(game->map, i, j + 1))))
				game->map[i][j] = 'C';
		}
	}
	printf("\n");
	i = -1;
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
		{
			if (game->map[i][j] == 'C')
				printf("\033[0;32m%c\033[0m", game->map[i][j]);
			else if (game->map[i][j] == '1')
				printf("\033[0;30m%c\033[0m", game->map[i][j]);
			else if (game->map[i][j] == '0')
				printf("\033[0;40m%c\033[0m", game->map[i][j]);
			else
				printf("%c", game->map[i][j]);
		}
		printf("\n");
	}

}