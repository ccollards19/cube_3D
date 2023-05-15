#include "../includes/cub3d.h"
#include <stdio.h>

/////////////////////////////////////////////////////////////

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	if (x < WIN_WIDTH && x >= 0 && y < WIN_HEIGHT && y >= 0)
	{
		*(unsigned int *)(img->offset + 
		(y * img->line_length + x * (img->bits_per_pixel / 8))) = color;
	}
}

unsigned int get_texture_color(t_img *img, int x, int y)
{
	if (x < img->width && x >= 0 && y < img->height && y >= 0)
	{
		return (*(unsigned int *)(img->offset + 
		(y * img->line_length + x * (img->bits_per_pixel / 8))));
	}
	return (0);
}

// player size = 1.8
// wall size = 3
// fov 60 degree
// optimisation possible by precomputing most values
void	print_ray_on_img(t_img *frame, t_ray *ray, int x, t_game *game)
{
	double 	lim1;
	double	lim2;
	double	y;
	double	y_texture;
	double	y_incr;
	int 	color;
 
	lim2 = (WIN_HEIGHT / 2) + (int)((WIN_HEIGHT / 2) * (1.2 / (ray->distance * tan(M_PI_4))));
	lim1 = (WIN_HEIGHT / 2) - (int)((WIN_HEIGHT / 2) * (1.8 / (ray->distance * tan(M_PI_4))));
	//printf("lim1 = %d lim2 = %d distance [%f]\n", lim1, lim2, distance);
	/*if (lim1 < 0)
		lim1 = 0;
	if (lim2 < 0)
		lim2 = 1000;
*/
	y = 0;
	y_texture = 0;
	y_incr = (ray->texture->height / fabs(lim2 - lim1));
	while (y < lim1)
  {
		my_mlx_pixel_put(frame, x, y, game->ceiling_color);
    y++;
  }
  while (lim1 < lim2)
	{
		color = get_texture_color(ray->texture, (int)(ray->texture_offset * ray->texture->width), (int)y_texture);
		my_mlx_pixel_put(frame, x, lim1, color);
		y++;
    lim1++;
		y_texture += y_incr;
	}
  while (y < 1000)
  {
		my_mlx_pixel_put(frame, x, y, game->floor_color);
    y++;
  }
}

void	*build_frame(t_ray *ray, t_game *game)
{
	int	i;

	i = 0;
  ray->x = game->player->x;
  ray->y = game->player->y;
  ray->x0 = game->player->x;
  ray->y0 = game->player->y;
  ray->distance = 0;
  ray->angle = (game->angle)[i].angle;
  ray->dx = (game->angle)[i].cos;
  ray->dx_inv = (game->angle)[i].cos_inv;
  ray->dy = (game->angle)[i].sin;
  ray->dy_inv = (game->angle)[i].sin_inv;
  ray->texture_offset = 0;
  ray->texture = 0;
 // printf("dx = %f, dy = %f angle = %f\n", ray->dx, ray->dy, ray->angle);
  while (i < RAY_NBR)
  {

    cast_ray(ray, game);
    print_ray_on_img(&game->frame, ray, i, game);
    //reset_ray();
    ray->x = game->player->x;
    ray->y = game->player->y;
    ray->x0 = game->player->x;
    ray->y0 = game->player->y;
    ray->distance = 0;
    ray->angle = (game->angle)[i].angle;
    ray->dx = (game->angle)[i].cos;
    ray->dx_inv = (game->angle)[i].cos_inv;
    ray->dy = (game->angle)[i].sin;
    ray->dy_inv = (game->angle)[i].sin_inv;
    ray->texture_offset = 0;
    ray->texture = 0;

    i++;
  }
  mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->frame.ptr, 0, 0);
  return (NULL);
}

