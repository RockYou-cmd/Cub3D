#include "cub3d.h"
#include "pics/redbrick.ppm"

int sum_of_rgb(int r, int g, int b)
{
	return ((65536 * r) + (512 * g) + b);
}

int main()
{
	data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, 2500, 1400, "cub3d");
	int x;
	int y;

	x = 0;
	y = 0;
	while(x < 32)
	{
		y = 0;
		while (y < 32)
		{
			int pixel = (y * 32 + x) * 3;
			mlx_pixel_put(data.mlx, data.win, x, y, sum_of_rgb(wall[pixel], wall[pixel + 1], wall[pixel + 2]));
			y ++;
		}
		x ++;
	}
    mlx_loop(data.mlx);
}
	// x ++;

