#include "cub3d.h"
#include "pics/wall1.ppm"
#include "pics/wall2.ppm"
#include "pics/wall3.ppm"
#include "pics/wall4.ppm"

void strip(float x1, float y1, float y2, int x_offset, int textures[])
{
	float y = 0;
	int red;
	int green;
	int blue;
	float inc = 0;
	while(y <= y2)
	{
		red = textures[(((int)inc * 32) + x_offset) * 3];
		green = textures[((((int)inc * 32) + x_offset) * 3) + 1];
		blue = textures[((((int)inc * 32) + x_offset) * 3) + 2];
		my_main_mlx_pixel_put(x1 , y1 + y, sum_of_rgb(red, green, blue)); 
		inc += (data.texture_size / y2);
		y ++;
	}
}

void read_textures()
{
	int x;
	int y;
	void *_img;
	int bits;
	int length;
	int end;
	_img = mlx_xpm_file_to_image(data.mlx, "pics/wall1.xpm", &x, &y);
	data.img_addr = (int *)mlx_get_data_addr(_img, &bits, &length, &end);
	// mlx_destroy_image(data.mlx, img);
}

void draw3D(float wall_hight , int i, int x_offset, int way)
{
	// (void)i;
	// (void)x_offset;
	(void)way;
	// (void)wall_hight;
	if (way)
		strip(i * data.rays.width, (data.window_hight / 2) - (wall_hight / 2), wall_hight, x_offset, wall1);
	else
		strip(i * data.rays.width, (data.window_hight / 2) - (wall_hight / 2), wall_hight, x_offset, wall2);
	main_dda(i * data.rays.width , 0 ,i * data.rays.width,(data.window_hight / 2) - (wall_hight / 2), data.props.f);
	main_dda(i * data.rays.width , (data.window_hight / 2) + (wall_hight / 2) ,i * data.rays.width,data.window_hight, data.props.c);
}