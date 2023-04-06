#include "cub3d.h"

void	terminate(t_game *game, char *msg)
{
	if (game->mlx_ptr && game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (msg ==  NULL)
		exit(0);
	else
	{
		ft_putstr_fd("Error\n\t", 2);
		ft_putstr_fd(msg, 2);
		exit(1);
	}
}
