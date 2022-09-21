#include "cub3d.h"
void	my_main_mlx_pixel_put(int x, int y, int color)
{
	char	*dst;
	if (x >= data.window_width || x <= 0 || y >= data.window_hight || y <= 0)
		return ;
	dst = data.addr + (y * data.line_length + x * (data.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
void	my_mini_mlx_pixel_put(int x, int y, int color)
{
	char	*dst;
	if (x >= data.window_width || x <= 0 || y >= data.window_hight || y <= 0)
		return ;
	// my_main_mlx_pixel_put(x, y, color);
		// return ;
	x /= 4;
	y /= 4;
	dst = data.addr + (y * data.line_length + x * (data.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void player()
{
	float r;
	float x;
	float y;
	float angle = 0;
	r = 5;
	while(r >= 0)
	{
		angle = 0;
		while(angle <= 10)
		{
			x = r * cos(angle) + data.player.x;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
			y = r * sin(angle) + data.player.y;
			my_mini_mlx_pixel_put(x, y, 16776960);
			angle += 0.1;
		}
		r -= 1;
	}
	x = data.player.x + (cos(data.player.rotationAngle) * 30);
	y = data.player.y + (sin(data.player.rotationAngle) * 30);
	dda(x, y);
}

void square_drawing(int ix, int iy, int color)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while(y <= data.square_size - 2)
	{
		x = 0;
		while(x <= data.square_size - 2)
		{
				my_mini_mlx_pixel_put(ix + x, iy + y, color);
			x ++;
		}
		y ++;
	}
}

void draw()
{
	int iy = 0;
	int ix = 0;
	
	mlx_clear_window(data.mlx, data.win);
	while (iy < data.map.rows)
	{
		ix = 0;
		while(data.map.array[iy][ix])
		{
			if (data.map.array[iy][ix] &&  data.map.array[iy][ix] == '1')
				square_drawing(ix * data.square_size, iy * data.square_size, 16775916);
			else if(data.map.array[iy][ix] && data.map.array[iy][ix] == '0')
				square_drawing(ix * data.square_size, iy * data.square_size, 2371579);
			// else 

			ix ++;
		}
		iy ++;
	}
	player();

}