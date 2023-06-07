#include "../includes/cub3d.h"

void ray_copy(t_ray *src, t_ray *dest)
{
	ft_memcpy(dest, src, sizeof(t_ray));
}

//////////////////////////////////////////////////////////////
/* move ray->x or ray->y to the next intersection with a tile
 * and update other values of the ray
 */
void	move_ray_x(t_ray *ray)
{
	if (ray->dx > 0)
		ray->x = ceil(ray->x + 0.000001);
	else if (ray->dx < 0)
		ray->x = floor(ray->x - 0.000001);
	//ray->x = round(ray->x);
	ray->distance = (ray->x - ray->x0) * ray->dx_inv;
	ray->y = (ray->distance * ray->dy) + ray->y0;
}

void	move_ray_y(t_ray *ray)
{
	if (ray->dy > 0)
		ray->y = ceil(ray->y + 0.000001);
	else if (ray->dy < 0)
		ray->y = floor(ray->y - 0.000001);
	//ray->y = round(ray->y);
	ray->distance = (ray->y - ray->y0) * ray->dy_inv;
	ray->x = (ray->distance * ray->dx) + ray->x0;
}

/* check if current tile contain an element
 * copy tmp ray into ray
 * retreive the corresponding texture pointer and offest
 * slight differences between the 2 function depending on the direction of the ray
 */
int	intersect_WE(t_ray *ray, t_ray *ray_tmp, t_game *game, char tile)
{
	tile = (game->map)[(int)(ray_tmp->x)][(int)(ray_tmp->y)];
	if (tile == '1')
	{
		ray_copy(ray_tmp, ray);
		//ray->asset = tile;
		//ray->asset = &((game->assets)[tile]);
		ray->texture = &(game->asset->WE);
		//ray->texture = (game->assets)[tile]->WE;
		ray->texture_offset = ray->y - floor(ray->y);
		//if ((game->assets)[tile]->stop)
		return (1);
	}
	return (0);
}

int	intersect_EA(t_ray *ray, t_ray *ray_tmp, t_game *game, char tile)
{
	tile = (game->map)[(int)(ray_tmp->x - 1)][(int)(ray_tmp->y)];
	if (tile == '1')
	{
		ray_copy(ray_tmp, ray);
		//ray->asset = tile;
		//ray->asset = &((game->assets)[tile]);
		ray->texture = &(game->asset->EA);
		//ray->texture = (game->assets)[tile]->EA;
		ray->texture_offset = ray->y - floor(ray->y);
		//if ((game->assets)[tile]->stop)
		return (1);
	}
	return (0);
}

int	intersect_NO(t_ray *ray, t_ray *ray_tmp, t_game *game, char tile)
{
	tile = (game->map)[(int)(ray_tmp->x)][(int)(ray_tmp->y - 1)];
	if (tile == '1')
	{
		ray_copy(ray_tmp, ray);
		//ray->asset = tile;
		//ray->asset = &((game->assets)[tile]);
		ray->texture = &(game->asset->NO);
		//ray->texture = (game->assets)[tile]->NO;
		ray->texture_offset = ray->x - floor(ray->x);
		//if ((game->assets)[tile]->stop)
		return (1);
	}
	return (0);
}

int	intersect_SO(t_ray *ray, t_ray *ray_tmp, t_game *game, char tile)
{
	tile = (game->map)[(int)(ray_tmp->x)][(int)(ray_tmp->y)];
	if (tile == '1')
	{
		ray_copy(ray_tmp, ray);
		//ray->asset = tile;
		//ray->asset = &((game->assets)[tile]);
		ray->texture = &(game->asset->SO);
		//ray->texture = (game->assets)[tile]->S0;
		ray->texture_offset = ray->x - floor(ray->x);
		//if ((game->assets)[tile]->stop)
		return (1);
	}
	return (0);
}

/* use two tmp rays 
 * cast one toward the next vertical intersection with a tile
 * the other toward the next horizontal intersection
 * check if tile is an asset
 * repeat until it finds a asset that stop the ray
 */
void	cast_ray(t_ray *ray, t_game *game)
{
	t_ray	ray_x;
	t_ray	ray_y;

	ray_copy(ray, &ray_x);
	ray_copy(ray, &ray_y);
	move_ray_x(&ray_x);
	move_ray_y(&ray_y);
	while (1)// assume player in empty tile
	{
		if (ray_x.distance <= ray_y.distance)
		{
			if ((ray->dx < 0 && intersect_EA(ray, &ray_x, game, 0)) ||
			intersect_WE(ray, &ray_x, game, 0))
				return ;
		}
		else if ((ray->dy < 0 && intersect_NO(ray, &ray_y, game, 0)) ||
			intersect_SO(ray, &ray_y, game, 0))
		{
				return ;
		}
		if (ray_x.distance <= ray_y.distance)
			move_ray_x(&ray_x);
		else
			move_ray_y(&ray_y);
	}
}
