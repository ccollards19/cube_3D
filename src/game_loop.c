#include "cub3d.h"

int	destroy(t_game *game)
{
	terminate(game, "Window got closed\n");
	return (1);
}

int	key_hook(int key, t_game *game)
{
	if (key == 49)
		game->color_change = 1;
	if (key == 46)
		(++game->should_cast && \
		((game->hide_minimap && game->hide_minimap--) || game->hide_minimap++));
	if (key == 53)
		exit(1);
	if (key == W)
		game->up = 1;
	if (key == S)
		game->down = 1;
	if (key == A)
		game->left = 1;
	if (key == D)
		game->right = 1;
	return (0);
}

int	relase_key_hook(int key, t_game *game)
{
	if (key == 49)
		game->color_change = 0;
	if (key == W)
		game->up = 0;
	if (key == S)
		game->down = 0;
	if (key == A)
		game->left = 0;
	if (key == D)
		game->right = 0;
	return (0);
}

int	loop_hook(t_game *game)
{
	int		cast;
	double	d_x;
	double	d_y;

	d_x = 0;
	d_y = 0;
	cast = handle_mouse(game) + input_management(game, d_x, d_y) \
	+ change_color(game) + game->firing;
	if (cast || game->should_cast)
	{
		game->should_cast = 0;
		raycast(game);
		if (!game->hide_minimap)
			minimap(game);
	}
	return (0);
}

int	mouse_hook(int key, int i, int j, t_game *game)
{
	(void)i;
	(void)j;
	if (key == 1)
	{
		if (game->firing < 2)
			game->firing++;
	}
	if (key == 2)
	{
		game->cursor.shape++;
		if (game->cursor.shape > CIRCLE)
			game->cursor.shape = CROSS;
	}
	game->should_cast = 1;
	return (0);
}

void	game_loop(t_game *game)
{
	mlx_hook(game->win_ptr, 17, 0, destroy, game);
	mlx_hook(game->win_ptr, 3, 1L << 0, relase_key_hook, game);
	mlx_hook(game->win_ptr, 2, 1L << 1, key_hook, game);
	mlx_mouse_hook(game->win_ptr, mouse_hook, game);
	mlx_loop_hook(game->mlx_ptr, loop_hook, game);
	mlx_loop(game->mlx_ptr);
}
