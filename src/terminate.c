#include "cub3d.h"

void	terminate(t_game *game, char *msg)
{
	if (game && game->mlx_ptr && game->win_ptr)
	{
		if (game->map_allocated)
			free_array(game->map);
		else
			free(game->map);
		free_array(game->file);
		mlx_destroy_image(game->mlx_ptr, game->minimap.ptr);
		mlx_destroy_image(game->mlx_ptr, game->frame.ptr);
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	}
	if (msg ==  NULL)
		exit(0);
	else
	{
		ft_putstr_fd("Error\n\t", 2);
		ft_putstr_fd(msg, 2);
		exit(1);
	}
}
