#include "cub3d.h"

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

int	get_nb_line(char *s)
{
	int		fd;
	char	*tmp;
	int		nb_line;

	nb_line = 0;
	fd = open(s, O_RDONLY);
	if (fd < 0)
		terminate(NULL, "file does not exist\n");
	tmp = get_next_line(fd);
	while (tmp)
	{
		if (!empty_line(tmp))
			nb_line++;
		safe_free(tmp);
		tmp = get_next_line(fd);
	}
	close(fd);
	return (nb_line + 1);
}

char	**get_file_array(char *s)
{
	char	**arr;
	int		fd;
	int		i;
	int		map;

	map = 0;
	i = -1;
	if (is_invalid_name(s))
		terminate(NULL, "invalid map name\n");
	arr = xmalloc(sizeof(char *) * get_nb_line(s));
	fd = open(s, O_RDONLY);
	while (1)
	{
		arr[++i] = get_next_line(fd);
		if (!arr[i])
			break ;
		if (arr[i] && empty_line(arr[i]))
		{
			safe_free(arr[i--]);
			continue;
		}
		(arr[i] && valid_map_line(arr[i]) && map++);
		if (map && !valid_map_line(arr[i]))
			terminate(NULL, "empty line in the map\n");
		else if (does_contain(arr[i], '\n') && ft_strlen(arr[i] - 2))
			arr[i][ft_strlen(arr[i]) - 2] = 0;
	}
	arr[i] = 0;
	return (arr);
}
