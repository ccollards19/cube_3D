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
 
	lim2 = 500 * (1 + (1.2 / ray->distance));
	lim1 = 500 * (1 - (1.8 / ray->distance));
	//printf("lim1 = %d lim2 = %d distance [%f]\n", lim1, lim2, distance);

	y = 0;
	y_texture = 0;//ray->texture->height *  //TODO;
	y_incr = (ray->texture->height / fabs(lim2 - lim1));

	while (y < 1000)
  {
    if (y < lim1)
    {
      my_mlx_pixel_put(frame, x, y, game->ceiling_color);
    }
    else if (y < lim2)
    {
      //if (color == 0)
        color = get_texture_color(ray->texture, (int)(ray->texture_offset * ray->texture->width), (int)y_texture);
      my_mlx_pixel_put(frame, x, y, color);
      lim1++;
      y_texture += y_incr;
    }
    else
    {
      my_mlx_pixel_put(frame, x, y, game->floor_color);
    }
    y++;
  }
}

void	*build_frame(t_ray *ray, t_game *game)
{
  int	i;
  double 	angle_incr;

  i = 0;
  angle_incr = (M_PI_2) / RAY_NBR;
  ray->angle -= M_PI_4;
  while (i < RAY_NBR)
  {

    cast_ray(ray, game);
    //printf("x = %f, y = %f, ray->distance = %f angle = %f\n", ray->x, ray->y, ray->distance, ray->angle);
    print_ray_on_img(&game->frame, ray, i, game);
    //reset_ray();
    ray->x = game->player->x;
    ray->y = game->player->y;
    ray->x0 = game->player->x;
    ray->y0 = game->player->y;
    ray->distance = 0;
    ray->angle = ray->angle + angle_incr;
    ray->dx = cos(ray->angle);
    ray->dx_inv = 1 / cos(ray->angle);
    ray->dy = sin(ray->angle);
    ray->dy_inv = 1 / sin(ray->angle);
    ray->texture_offset = 0;
    ray->texture = 0;

    i++;
  }
  mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->frame.ptr, 0, 0);
  return (NULL);
}

