#include "minilibx-linux/mlx.h"
#include <stdlib.h>

int main()
{
	void *mlx;
	void *win;

	mlx = mlx_init();
	if(!mlx)
		return 1;
	
	win = mlx_new_window(mlx, 800, 600, "samet");
	if (!win)
		return 1;

	mlx_string_put(mlx, win, 300, 100, 0xFFFFFF, "SAMET");
	mlx_hook(win, 17, 0, (void *)exit, 0);
	mlx_loop(mlx);
	return 0;
}


/*int main()
{
	void *mlx; //Minilibx bağlantı noktası
	void *win; //Pencere bağlantısı

	// 1- minilibx'i başlat
	mlx = mlx_init();
	if (!mlx)
		return 1; //başarısız başlatmada program sonlandırma

	// 2- .yeni bir pencere oluştur
	win = mlx_new_window(mlx, 800, 600, "Minilibx Ornek");
	if (!win)
		return 1; //pencere oluşturulmazsa programı sonlandır

	mlx_clear_window(mlx, win);

	mlx_string_put(mlx, win, 300, 200, 0xFF0000, "minilibx denemesi");

	// 3- Programı başlat
	mlx_loop(mlx); //minilibx olay döngüsü, pencerenin açık kalmasını sağlar.
	return 0;
}*/