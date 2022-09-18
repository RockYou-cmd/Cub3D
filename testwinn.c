#include "cub3d.h"

int sum_of_rgb(int t, int r, int g, int b)
{
	return ((t * 16777216) + (65537 * r) + (256 * g) + b);
}

int main()
{
	data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, 500, 500, "cub3d");
	int x;
	int y;

	x = 0;
	y = 0;
	while(y <= 100 - 2)
	{
		x = 0;
		while(x <= 100 - 2)
		{
				mlx_pixel_put(data.mlx, data.win, x, y, sum_of_rgb(222, 255, 161, 227));
			x ++;
		}
		y ++;
	}
    mlx_loop(data.mlx);

}