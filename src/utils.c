#include "cub3d.h"

void	*xmalloc(int mem_size)
{
	void	*mem_alloc;

	mem_alloc = malloc(mem_size);
	if (!mem_alloc)
		exit(1);
	return (mem_alloc);
}

void	safe_free(void	*mem_allocated)
{
	if (mem_allocated)
		free(mem_allocated);
	mem_allocated = NULL;
}

int	print_err(int nb_arg, ...)
{
	va_list	lst;
	int		i;

	i = -1;
	va_start(lst, nb_arg);
	while (++i < nb_arg)
		ft_putstr_fd((char *)va_arg(lst, char *), 2);
	va_end(lst);
	return (1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void	free_array(char	**arr)
{
	int	i;

	i = 0;
	while (arr[i])
		safe_free(arr[i++]);
	safe_free(arr);
}
