#include "cub3d.h"

void	free_gun_effect(t_game *game)
{
	mlx_destroy_image(game->mlx_ptr, game->gun_effect[0].ptr);
	mlx_destroy_image(game->mlx_ptr, game->gun_effect[1].ptr);
	mlx_destroy_image(game->mlx_ptr, game->gun_effect[2].ptr);
	mlx_destroy_image(game->mlx_ptr, game->gun_effect[3].ptr);
	mlx_destroy_image(game->mlx_ptr, game->gun_effect[4].ptr);
	mlx_destroy_image(game->mlx_ptr, game->gun_effect[5].ptr);
	mlx_destroy_image(game->mlx_ptr, game->gun_effect[6].ptr);
}

void	free_img(t_game *game)
{
	if (game->asset != NULL)
	{
		mlx_destroy_image(game->mlx_ptr, game->asset->DO.ptr);
		mlx_destroy_image(game->mlx_ptr, game->asset->EA.ptr);
		mlx_destroy_image(game->mlx_ptr, game->asset->NO.ptr);
		mlx_destroy_image(game->mlx_ptr, game->asset->WE.ptr);
		mlx_destroy_image(game->mlx_ptr, game->asset->SO.ptr);
	}
	if (game->minimap.ptr != NULL)
		mlx_destroy_image(game->mlx_ptr, game->minimap.ptr);
	if (game->player != NULL)
		free(game->player);
	if (game->gun_effect[0].ptr != NULL)
		free_gun_effect(game);
	if (game->gun.ptr != NULL)
		mlx_destroy_image(game->mlx_ptr, game->gun.ptr);
	if (game->gun_sprite.ptr != NULL)
		mlx_destroy_image(game->mlx_ptr, game->gun_sprite.ptr);
	if (game->frame.ptr != NULL)
		mlx_destroy_image(game->mlx_ptr, game->frame.ptr);
}

void	terminate(t_game *game, char *msg)
{
	if (game && game->mlx_ptr && game->win_ptr)
	{
		if (game->map_allocated)
			free_array(game->map);
		else
			free(game->map);
		free_array(game->file);
		free_img(game);
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	}
	if (msg == NULL)
		exit(0);
	else
	{
		ft_putstr_fd("Error\n\t", 2);
		ft_putstr_fd(msg, 2);
		exit(1);
	}
}
