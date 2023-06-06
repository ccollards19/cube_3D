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
# define M_PI_8 0.3926905
# define AGL(x) x > 2147483647 ? 1 : 0
# define ESC 53
# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124
# define W 13
# define A 2
# define S 1
# define D 0
# define PI2 2 * M_PI
# define SIN_10 0.173648
# define SIN_20 0.342020
# define SIN_30 0.500000
# define SIN_40 0.642788
# define SIN_50 0.766044
# define SIN_60 0.866025
# define SIN_70 0.939693
# define SIN_80 0.984808
# define SIN_90 1.000000

//# define SIN_2(A) A < M_PI ? : SIN_3(A)
//# define SIN(A) A < M_PI_2 ? A < M_PI_4 ? SIN_3(A) : A < M_PI_8 ? SIN_10 : SIN_20: SIN_2(A)


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
	int	width;
	int	height;
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
	t_img	*texture;
} t_ray;

typedef struct s_player
{
	double 	angle;
	double	x;
	double	y;
	int		fov;
	size_t 	ammo;
	size_t	hp;
	size_t	speed;
}	t_player;

typedef	struct s_asset {
	char	id;
	int	stop;
	t_img	NO;
	t_img	SO;
	t_img	WE;
	t_img	EA;
} t_asset;

typedef enum e_color
{
	CEILING,
	FLOOR
}t_color;

typedef struct s_game
{
	t_player	*player;
	t_asset		*asset;
	t_img		frame;
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
	int			**render_array;
	int			up;
	int			down;
	int			left;
	int			right;
	int			mouse[2];
	int			hide_minimap;
	int			should_cast;
	int			color_type;
}t_game;

//utils.c
void	*xmalloc(int mem_size);
void	safe_free(void	*mem_allocated);
int		print_err(int nb_arg, ...);
int		ft_strcmp(const char *s1, const char *s2);
void	free_array(char	**arr);
int		array_size(char **arr);
//terminate.c
void	terminate(t_game *game, char *msg);

//game_loop.h
void	game_loop(t_game *game);
int		destroy(t_game *game);
int		key_hook(int keycode, t_game *game);
int		loop_hook(t_game *game);

//parsing.c
char	**get_file_array(char *s);
char	*get_path(char **file, t_path path);
int		get_color(char **file, t_color color);
double	get_init_angle(t_game *game);
int		set_player_position(t_game *game);

//raycasting.c
void	cast_ray(t_ray *ray, t_game *game);

//render.c
void	*build_frame(t_ray *ray, t_game *game);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

//syntax.c

int		valid_format(char *s);
int		is_invalid_name(char *s);
int		empty_line(char *s);
int		valid_map_line(char *s);

//minimap.c
char	**get_map(char **file);
void	minimap(t_game *game);
int		trgb(int t, int r, int g, int b);
//game_loop_utils
int		handle_mouse(t_game *game);
int		is_wall(char **map, double y, double x);
void	raycast(t_game *game);
int		input_management(t_game *game, double d_x, double d_y);
void	change_color(t_game *game);

//minimap2.c
void	print_square(t_img *minimap, int i, int j, int color);
void	print_player(t_img *minimap, double i, double j, int color);
void	print_player_fov(t_img *minimap, t_game *game, int color);
void	print_outer_circle(t_img *img, int pos, int inner_radius, int color);
void	print_element(t_img *minimap, t_game *game, int i, int j);
#endif
