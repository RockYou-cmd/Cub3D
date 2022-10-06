#include "cub3d.h"
#include "pics/wall1.ppm"

int sum_of_rgb(int r, int g, int b)
{
	return ((65536 * r) + (256 * g) + b);
}

int main()
{
	data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, 200, 200, "cub3d");
	int x1;
	int y1;
	void *img;
	void *img2;
	// int *addr;
	// int bits;
	// int length;
	// int end;
	img = mlx_xpm_file_to_image(data.mlx, "pics/wall1.xpm", &x1, &y1);
	img2 = mlx_xpm_file_to_image(data.mlx, "pics/wall1.xpm", &x1, &y1);
	// addr = (int *)mlx_get_data_addr(img, &bits, &length, &end);
	// printf("x : %d, y : %d\n", x1, y1);
	// mlx_destroy_image(data.mlx, img);
	// int x;
	// int y;

	// x = 0;
	// y = 0;
	// while(x < 50)
	// {
	// 	y = 0;
	// 	while (y < 50)
	// 	{
	// 		int pixel = (y * 50 + x);
	// 		mlx_pixel_put(data.mlx, data.win, x, y, addr[pixel]);
	// 		// mlx_pixel_put(data.mlx, data.win, x, y, addr[pixel]);
	// 		y ++;
	// 	}
	// 	x ++;
	// }
    // mlx_loop(data.mlx);
}
	// x ++;

