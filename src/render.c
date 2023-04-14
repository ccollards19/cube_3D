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

// player size = 1.8
// wall size = 3
// fov 60 degree
// optimisation possible by precomputing most values
void	print_ray_on_img(t_img *frame, double distance, int x)
{
	int y;
	int lim1;
	int lim2;
	
 
	lim2 = (WIN_HEIGHT / 2) + (int)((WIN_HEIGHT / 2) * (1.2 / (distance * tan(M_PI_4))));
	lim1 = (WIN_HEIGHT / 2) - (int)((WIN_HEIGHT / 2) * (1.8 / (distance * tan(M_PI_4))));
	y = 0;
	//printf("lim1 = %d lim2 = %d\n", lim1, lim2);
	while (y < lim1)
	{
		//print_ceiling();
		//printf("x = %d y = %d\n", x, y);
		my_mlx_pixel_put(frame, x, y, red);
		y++;
	}
	while (y < lim2)
	{       
		//printf("x = %d y = %d\n", x, y);
		my_mlx_pixel_put(frame, x, y, blue);
		y++;
	}
	while (y < 1000)
	{
		//printf("x = %d y = %d\n", x, y);
		//print_floor();
		my_mlx_pixel_put(frame, x, y, green);
		y++;
	}
	y = 0;
}

void	*build_frame(t_ray *ray, t_game *game)
{
	int	i;
	double 	angle_incr;
	t_img	frame;

	i = 0;
	angle_incr = (M_PI_2 / 3) / RAY_NBR;
	frame.ptr = mlx_new_image(game->mlx_ptr, 1200, 1200);//test version
	frame.offset = mlx_get_data_addr(frame.ptr, &frame.bits_per_pixel, &frame.line_length, &frame.endian);//test version
	while (i < RAY_NBR)
	{

		cast_ray(ray);
		print_ray_on_img(&frame, ray->distance, i);
		//reset_ray();
		ray->x = game->player->x;
		ray->y = game->player->y;
		ray->x0 = game->player->x;
		ray->y0 = game->player->y;
		ray->angle = ray->angle + angle_incr;
		ray->dx = sin(ray->angle);
		ray->dx_inv = 1 / sin(ray->angle);
		ray->dy = cos(ray->angle);
		ray->dy_inv = 1 / cos(ray->angle);
		ray->texture_offset = 0;

		//printf("ray->distance = %f angle = %f\n", ray->distance, ray->angle);
		i++;
	}
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, frame.ptr, 0, 0);
	mlx_destroy_image(game->mlx_ptr, frame.ptr);
	return (NULL);
}

