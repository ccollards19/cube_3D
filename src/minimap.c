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
	i = 4;
	while (file[++i])
		len++;
	map = xmalloc(sizeof(char *) * len);
	len = 0;
	i = 4;
	while (file[++i])
		map[len++] = file[i];
	map[len] = NULL;
	return (map);

}

void	minimap(void)
{
	return ;
}
