#include "../includes/cub3d.h"

void	init_cursor(t_game *game)
{
	game->cursor.img.ptr = mlx_new_image(game->mlx_ptr, 60, 60);
	game->cursor.img.offset = mlx_get_data_addr(game->cursor.img.ptr, \
	&game->cursor.img.bits_per_pixel, &game->cursor.img.line_length, \
	&game->cursor.img.endian);
	game->cursor.hover = 0;
	game->cursor.shape = DOT;
}

void	print_shape(t_img *img, enum e_shape shape, int color, int pos[2])
{
	int dist;

	my_mlx_pixel_put(img, pos[0], pos[1], trgb(255, 0, 0, 0));
	dist = ((30 - pos[0]) * (30 - pos[0])) + \
	((30 - pos[1]) * (30 - pos[1]));
	if (shape == CROSS && ((pos[0] >= 28 && pos[0] <= 32) \
	|| (pos[1] >= 28 && pos[1] <= 32)))
		my_mlx_pixel_put(img, pos[0], pos[1], color);
	if (shape == DOT && dist <= 36)
		my_mlx_pixel_put(img, pos[0], pos[1], color);
	if (shape == CIRCLE && dist <= 64 && dist >= 36)
		my_mlx_pixel_put(img, pos[0], pos[1], color);
}

void	print_cursor(t_game *game, int i, int j)
{
	int pos[2];

	while (++i < 60)
	{
		j = -1;
		while (++j < 60)
		{
			pos[0] = i;
			pos[1] = j;
			if (game->cursor.hover)
				print_shape(&game->cursor.img, game->cursor.shape, \
				trgb(0, 255, 1, 1), pos);
			else
				print_shape(&game->cursor.img, game->cursor.shape, \
				trgb(0, 1, 255, 1), pos);
		}
	}
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, \
	game->cursor.img.ptr, 420, 420);
}