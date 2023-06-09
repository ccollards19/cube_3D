#include "../includes/cub3d.h"

void	shoot(t_game *game)
{
	static int	tic;
	static int	state;
	static int	clock;

	clock++;
	if ((game->down || game->up || state) && !(clock % 6))
	{
		if (!state)
			state = 15;
		else if (state == 5)
			state = -15;
		else
			state = 0;
	}
	if (!game->firing)
		print_sprite(&game->gun, game->pos[tic], game->dimension, &game->gun_sprite);
	else
	{
		game->sprite_frame++;
		if (game->sprite_frame > 6)
			game->sprite_frame = 0;
		if ((game->sprite_frame % 2) && ++tic > 2)
		{
			if (game->firing)
				game->firing--;
			if (!game->firing)
				game->should_cast = 1;
			tic = 0;
		}
		if (game->firing)
			mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, \
			game->gun_effect[game->sprite_frame].ptr, 495, 680);
		print_sprite(&game->gun, game->pos[tic], game->dimension, &game->gun_sprite);
	}
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, \
	game->gun.ptr, 460, 650 + state);
}