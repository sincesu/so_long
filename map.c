#include "libs/minilibx-linux/mlx.h"

int main()
{
	void *mlx;
	void *mlx_win;
	void *img;
	int img_width;
	int img_height;

	mlx = mlx_init();
	if(!mlx)
		return 0;

	mlx_win = mlx_new_window(mlx, 500, 500, "malenes");
	img = mlx_xpm_file_to_image(mlx, "./images/exit.xpm", &img_width, &img_height);
	mlx_put_image_to_window(mlx, mlx_win, img, 50, 50);
	mlx_loop(mlx);
}