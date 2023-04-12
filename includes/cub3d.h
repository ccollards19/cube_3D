#ifndef CUB3D_H
# define CUB3D_H
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <errno.h>
# include "../mlx/mlx.h"
# include <stdlib.h>
# include "../libft/libft.h"
# include "color.h"
#include <stdio.h>//test

# define RAY_NBR 1000
# define WIN_WIDTH 1000
# define WIN_HEIGHT 1000

# define AGL(x) x > 2147483647 ? 1 : 0


typedef enum e_path
{
	EA,
	SO,
	WE,
	NO
}t_path;

typedef struct	s_img {
	void	*ptr;
	char	*offset;
	int	bits_per_pixel;
	int	line_length;
	int	endian;
}				t_img;

/* need to change texture and texture offset to chained list 
 * to allow for multiple elements to be visible when behind each other
 */
typedef struct s_ray {
	double	distance;
	double	angle;
	double	x0;
	double	y0;
	double	x;
	double	y;
	double	dx;
	double	dy;
	double	dx_inv;
	double	dy_inv;
	double	texture_offset;
//	enum	texture;
} t_ray;

typedef struct s_player
{
	size_t 	angle;
	float	x;
	float	y;
	int		fov;
	int		ammo;
	size_t	hp;
	size_t	speed;
}t_player;

typedef enum e_color
{
	CEILING,
	FLOOR
}t_color;

typedef struct s_game
{
	t_player	*player;
	void		*mlx_ptr;
	void		*win_ptr;
	char		**file;
	char		**map;
	char		*NO_path;
	char		*SO_path;
	char		*WE_path;
	char		*EA_path;
	int			floor_color;
	int			ceiling_color;
}t_game;

//utils.c
void	*xmalloc(int mem_size);
void	safe_free(void	*mem_allocated);
int		print_err(int nb_arg, ...);
int		ft_strcmp(const char *s1, const char *s2);
void	free_array(char	**arr);

//terminate.c
void	terminate(t_game *game, char *msg);

//game_loop.h
void	game_loop(t_game *game);

//parsing.c
char	**get_file_array(char *s);
char	*get_path(char **file, t_path path);
int		get_color(char **file, t_color color);

//raycasting.c
void	cast_ray(t_ray *ray);

//render.c
void	*build_frame(t_ray *ray, t_game *game);

//syntax.c

int	valid_format(char *s);
int	is_invalid_name(char *s);
int	empty_line(char *s);
int	valid_map_line(char *s);

//minimap.c
char	**get_map(char **file);
void	minimap(t_game *game);
#endif
