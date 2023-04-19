#include "cub3d.h"

int	set_player_position(t_game *game)
{
	int		i;
	char	*search;

	i = 0;
	while (game->map[i])
	{
		search = ft_strchr(game->map[i], 'N');
		if (!search)
			search = ft_strchr(game->map[i], 'E');
		if (!search)
			search = ft_strchr(game->map[i], 'S');
		if (!search)
			search = ft_strchr(game->map[i], 'W');
		if (search)
			break ;
		i++;
	}
	if (!game->map[i])
		return (0);
	printf("found\n");
	game->player->x = i;
	game->player->y = search - game->map[i];
	return (1);
}

double	get_init_angle(t_game *game)
{
	int		i;
	double		dir;

	dir = 0;
	i = -1;
	while (game->map[++i])
	{
		if (does_contain(game->map[i], 'E') || \
		(++dir && does_contain(game->map[i], 'N')) || \
		(++dir && does_contain(game->map[i], 'W')) || \
		(++dir && does_contain(game->map[i], 'S')))
			return (M_PI_4 * dir);
		else
			dir = 0;
	}
	return (0);
}

int	get_color(char **file, t_color color)
{
	int		i;
	char	**rgb;
	int		int_color;

	int_color = 0;
	i = 0;
	while (file[i])
	{
		if ((color == FLOOR && !ft_strncmp(file[i], "F", 1) && \
		ft_strlen(file[i]) > 6 && i == 4) || (color == CEILING && \
		!ft_strncmp(file[i], "C", 1) && ft_strlen(file[i]) > 6 && i == 5))
			break ;
		i++;
	}
	if (!file[i] || !valid_format(file[i] + 2))
		terminate(NULL, "syntax of .cub not respected2\n");
	rgb = ft_split(file[i] + 2, ',');
	int_color += ft_atoi(rgb[0]) << 16;
	int_color += (ft_atoi(rgb[1]) << 8) + ft_atoi(rgb[2]);
	free_array(rgb);
	return (int_color);
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

int	get_buffer_size(char *s)
{
	int		fd;
	char	tmp;
	int		tot;

	tot = 0;
	fd = open(s, O_RDONLY);
	if (fd < 0)
		terminate(NULL, "file does not exist\n");
	while (read(fd, &tmp, 1))
		tot++;
	close(fd);
	return (tot);
}

char	**get_file_array(char *s)
{
	char	**arr;
	int		fd;
	char 	*buf;
	int		size;

	if (is_invalid_name(s))
		terminate(NULL, "invalid map name\n");
	size = get_buffer_size(s);
	buf = xmalloc(size + 1);
	fd = open(s, O_RDONLY);
	read(fd, buf, size);
	buf[size]= 0;
	arr = ft_split(buf, '\n');
	safe_free(buf);
	return (arr);
}
