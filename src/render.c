#include "../includes/cub3d.h"

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
void	print_ray_on_img(t_img *frame, t_ray *ray, int x)
{
	double 	lim1;
	double	lim2;
	double	y;
	double	y_incr;
	int 	color;
 
	lim2 = (WIN_HEIGHT / 2) + (int)((WIN_HEIGHT / 2) * (1.2 / (ray->distance * tan(M_PI_4))));
	lim1 = (WIN_HEIGHT / 2) - (int)((WIN_HEIGHT / 2) * (1.8 / (ray->distance * tan(M_PI_4))));
	//printf("lim1 = %d lim2 = %d distance [%f]\n", lim1, lim2, distance);
	if (lim1 < 0)
		lim1 = 0;
	if (lim2 < 0)
		lim2 = 1000;
	y = 0;
	y_incr = (ray->texture->height / fabs(lim2 - lim1));
	while (lim1 < lim2)
	{
		color = get_texture_color(ray->texture, (int)(ray->texture_offset * ray->texture->width), y);
		my_mlx_pixel_put(frame, x, lim1, color);
		lim1++;
		y += y_incr;
	}
}

void	*build_frame(t_ray *ray, t_game *game)
{
	int	i;
	double 	angle_incr;
	t_img	frame;

	i = 0;
	angle_incr = (M_PI_2) / RAY_NBR;
	frame.ptr = mlx_new_image(game->mlx_ptr, 1000, 1000);//test version
	frame.offset = mlx_get_data_addr(frame.ptr, &frame.bits_per_pixel, &frame.line_length, &frame.endian);//test version
	while (i < RAY_NBR)
	{

		cast_ray(ray, game);
		//printf("x = %f, y = %f, ray->distance = %f angle = %f\n", ray->x, ray->y, ray->distance, ray->angle);
		print_ray_on_img(&frame, ray, i);
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
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, frame.ptr, 0, 0);
	mlx_destroy_image(game->mlx_ptr, frame.ptr);
	return (NULL);
}

