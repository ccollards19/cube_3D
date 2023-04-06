#include "cube_3D.h"

void	terminate(char *msg, t_game *game)
{
	if (game->mlx_pt && game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (msg ==  NULL)
		exit(0);
	else
	{
		putstr_fd("Error\n\t", 2);
		putstr_fd(msg, 2);
		exit(1);
	}
}
