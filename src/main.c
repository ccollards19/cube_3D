#include "mlx.h"

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	void *mlx_ptr = mlx_init();
	void *win_ptr = mlx_new_window(mlx_ptr, 1000, 1000, "test");
	(void)win_ptr;
	mlx_loop(mlx_ptr);
	return (0);
}
