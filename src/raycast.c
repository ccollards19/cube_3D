#include "../includes/cub3d.h"

/*int map_tmp_G[24][24] =
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};//test*/

void ray_copy(t_ray *src, t_ray *dest)
{
	ft_memcpy(dest, src, sizeof(t_ray));//TODO add the ft_ back
}

int pseudo_cast(double nbr)
{
	if (fabs(nbr - round(nbr)) < 0.01)
		return ((int)round(nbr));
	return ((int)nbr);
}

//////////////////////////////////////////////////////////////
/* beware of edge cases like dx = 0
 */
void	move_ray_x(t_ray *ray)
{
	if (ray->dx > 0)
		ray->x = ceil(ray->x + 0.001);
	else if (ray->dx < 0)
		ray->x = floor(ray->x - 0.001);	
	ray->x = round(ray->x);//should insure that cast work as it should
	ray->distance = (ray->x - ray->x0) * ray->dx_inv;
	ray->y = (ray->distance * ray->dy) + ray->y0;
}

void	move_ray_y(t_ray *ray)
{
	if (ray->dy > 0)
		ray->y = ceil(ray->y + 0.001);
	else if (ray->dy < 0)
		ray->y = floor(ray->y - 0.001);
	ray->y = round(ray->y);
	ray->distance = (ray->y - ray->y0) * ray->dy_inv;
	ray->x = (ray->distance * ray->dx) + ray->x0;
	//printf("test\n");
}

/* check if current tile contain an element
 * need to add more logic things other than walls
 */
<<<<<<< HEAD
int	intersect_x(t_ray *ray, t_ray *ray_tmp/*, int *map_tmp_G[]*/)
=======
int	intersect(t_ray *ray, t_ray *ray_tmp, int *map_tmp_G[])
>>>>>>> cab41e4 (lol)
{
	int tile;
	
	if (ray->dx < 0)
		tile = map_tmp_G[pseudo_cast(ray_tmp->x - 1)][pseudo_cast(ray_tmp->y)];
	else
		tile = map_tmp_G[pseudo_cast(ray_tmp->x)][pseudo_cast(ray_tmp->y)];
	if (tile != 0)
	{
		//usleep(1000000);
		//printf("tile = %d in map_tmp_G[%d][%d]\n", tile, pseudo_cast(ray_tmp->x), pseudo_cast(ray_tmp->y)); 
		ray_copy(ray_tmp, ray);
		ray->texture_offset = 1;//tmp for testing only
		// other logic to add correct texture and shit
		if (tile == 1)
			return (1);
	}
	return (0);
}

int	intersect_y(t_ray *ray, t_ray *ray_tmp/*, int *map_tmp_G[]*/)
{
	int tile;
	
	if (ray->dy < 0)
		tile = map_tmp_G[pseudo_cast(ray_tmp->x)][pseudo_cast(ray_tmp->y - 1)];
	else
		tile = map_tmp_G[pseudo_cast(ray_tmp->x)][pseudo_cast(ray_tmp->y)];
	if (tile != 0)
	{
		//printf("tile = %d in map_tmp_G[%d][%d]\n", tile, pseudo_cast(ray_tmp->x), pseudo_cast(ray_tmp->y)); 
		ray_copy(ray_tmp, ray);
		ray->texture_offset = 1;//tmp for testing only
		// other logic to add correct texture and shit
		if (tile == 1)
			return (1);
	}
	return (0);
}

void	cast_ray(t_ray *ray, int **map_tmp_G)
{
	t_ray	ray_x;
	t_ray	ray_y;

	ray_copy(ray, &ray_x);
	ray_copy(ray, &ray_y);
	//printf("%f, %f, %f \n%f, %f \n%f, %f\n", ray->x, ray->y, ray->angle, ray->dx, ray->dx_inv, ray->dy, ray->dy_inv);//test
	while (ray->texture_offset != 1)//for testing only
	{
		//printf("//////////////////////////////\n");
		//printf("%f, %f, %f\n", ray_x.x, ray_x.y, ray_x.distance);
		//printf("%f, %f, %f\n\n", ray_y.x, ray_y.y, ray_y.distance);
		if (ray_x.distance <= ray_y.distance)
			move_ray_x(&ray_x);
		else
			move_ray_y(&ray_y);
		//printf("%f, %f, %f\n", ray_x.x, ray_x.y, ray_x.distance);
		//printf("%f, %f, %f\n", ray_y.x, ray_y.y, ray_y.distance);
		if (ray_x.distance <= ray_y.distance)
<<<<<<< HEAD
			intersect_x(ray, &ray_x/*, map_tmp_G*/);
		else
			intersect_y(ray, &ray_y/*, map_tmp_G*/);
=======
			intersect(ray, &ray_x, map_tmp_G);
		else
			intersect(ray, &ray_y, map_tmp_G);
>>>>>>> cab41e4 (lol)
	}
	//printf("angle = %f, distance %f, x = %f, y = %f\n", ray->angle, ray->distance, ray->x, ray->y);//test
}
/*
int main()
{
	t_game game;
	game.mlx_ptr = mlx_init();
	game.win_ptr = mlx_new_window(game.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Cube_3D");

	t_ray ray;
	ray.texture_offset = 0;
	ray.x = 3.1;
	ray.y = 3.1;
	ray.x0 = 3.1;
	ray.y0 = 3.1;
	ray.angle = 0;
	ray.dx = sin(ray.angle);
	ray.dx_inv = 1 / sin(ray.angle);
	ray.dy = cos(ray.angle);
	ray.dy_inv = 1 / cos(ray.angle);
	while (ray.angle > M_PI * 2)
	{
		cast_ray(&ray);
		ray.texture_offset = 0;
		ray.x = 3.1;
		ray.y = 3.1;
		ray.x0 = 3.1;
		ray.y0 = 3.1;
		ray.angle += 0.05;
		ray.dx = sin(ray.angle);
		ray.dx_inv = 1 / sin(ray.angle);
		ray.dy = cos(ray.angle);
		ray.dy_inv = 1 / cos(ray.angle);
	}

}
*/
