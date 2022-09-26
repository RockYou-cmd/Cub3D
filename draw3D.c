#include "cub3d.h"
#include "pics/wall1.ppm"
#include "pics/wall2.ppm"
#include "pics/wall3.ppm"
#include "pics/wall4.ppm"

void draw3D(float wall_hight , int i, int x_offset, int way)
{
	if (way)
		strip(i * data.rays.width, (data.window_hight / 2) - (wall_hight / 2), wall_hight, x_offset, wall1);
	else
		strip(i * data.rays.width, (data.window_hight / 2) - (wall_hight / 2), wall_hight, x_offset, wall2);
	main_dda(i * data.rays.width , 0 ,i * data.rays.width,(data.window_hight / 2) - (wall_hight / 2), data.props.f);
	main_dda(i * data.rays.width , (data.window_hight / 2) + (wall_hight / 2) ,i * data.rays.width,data.window_hight, data.props.c);
}