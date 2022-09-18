#include "cub3d.h"

void strip(float x1, float y1, float x2, float y2, int color)
{
	int x = 0;
	int y = 0;
	while(y <= y2)
	{
		x = 0;
		while(x <= x2)
		{
				my_main_mlx_pixel_put(x1 + x, y1 + y, color); 
			x ++;
		}
		y ++;
	}
}

void dda(float x2, float y2)
{
	float step;
	float x;
	float y;
	float dx;
	float dy;
	int i;

	x = data.player.x;
	y = data.player.y;
	dx = x2 - x;
	dy = y2 - y;
	if (fabs(dx) > fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	dx /= step;
	dy /= step;
	i = 1;
	while(i <= step)
	{
		my_mini_mlx_pixel_put(x, y, 255);
		x += dx;
		y += dy;
		i ++;
	}
}
void main_dda(float x, float y, float x2, float y2, int color)
{
	float step;
	float dx;
	float dy;
	int i;

	dx = x2 - x;
	dy = y2 - y;
	if (fabs(dx) > fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	dx /= step;
	dy /= step;
	i = 1;
	while(i <= step)
	{
		my_main_mlx_pixel_put(x, y, color);
		x += dx;
		y += dy;
		i ++;
	}
}

float distance(float x, float y)
{
	return sqrt((x - data.player.x) * (x - data.player.x) + (y - data.player.y) * (y - data.player.y));
}

float angle_corrector(float angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle = (2 * M_PI) + angle;
		return angle;
}

// int hcast(float nextX, float nextY)
// {
// 	while (nextX >= 0 && nextX <= data.window_width && nextY >= 0 && nextY <=data.window_hight)
// 	{
// 		if (wall_check(nextX, nextY))
// 		{
// 			data.rays.horz_wall_hitx = nextX;
// 			data.rays.horz_wall_hity = nextY;
// 			return 1;
// 		}
// 		else
// 		{
// 			nextX += data.rays.hstepx;
// 			nextY += data.rays.hstepy; 
// 		}
// 	}
// 	return 0;
// }
// int vcast(float nextX, float nextY)
// {
// 	while (nextX >= 0 && nextX <= data.window_width && nextY >= 0 && nextY <=data.window_hight)
// 	{
// 		if (wall_check(nextX, nextY))
// 		{
// 			data.rays.vert_wall_hitx = nextX;
// 			data.rays.vert_wall_hity = nextY;
// 			return 1;
// 		}
// 		else
// 		{
// 			nextX += data.rays.vstepx;
// 			nextY += data.rays.vstepy; 
// 		}
// 	}
// 	return 0;
// }

void check_ray(float ray_angle, int i)
{
	float x;
	float y;
	float walldistance;
	float wall_hight;
	float hit_distance;
	int way = 0;
	ray_angle = angle_corrector(ray_angle);
	data.rays.down = ray_angle > 0 && ray_angle < M_PI;
	data.rays.up = !data.rays.down;
	data.rays.right = ray_angle < M_PI * 0.5 || ray_angle > M_PI * 1.5;
	data.rays.left = !data.rays.right;
	horizon_check(ray_angle);
	vertic_check(ray_angle);
	if (data.rays.hhited)
		data.rays.hdistance = distance(data.rays.horz_wall_hitx, data.rays.horz_wall_hity);
	else
		data.rays.hdistance =  INT32_MAX;
	if (data.rays.vhited)
		data.rays.vdistance = distance(data.rays.vert_wall_hitx, data.rays.vert_wall_hity);
	else
		data.rays.vdistance =  INT32_MAX;
	if (data.rays.hdistance < data.rays.vdistance)
	{
		way = 1;
		hit_distance = data.rays.hdistance ;
		x = data.rays.horz_wall_hitx;
		y = data.rays.horz_wall_hity;
	}
	else
	{
		hit_distance = data.rays.vdistance ;
		x = data.rays.vert_wall_hitx;
		y = data.rays.vert_wall_hity;
	}
	hit_distance = hit_distance * cos(ray_angle - data.player.rotationAngle);
	walldistance = (data.window_width / 2) / tan(data.player.fov_angle / 2);
	wall_hight = (40 / hit_distance) * walldistance;
	// i = 5;
	if (way)
		strip(i * data.rays.width, (data.window_hight / 2) - (wall_hight / 2), data.rays.width, wall_hight, 16777140);
	else
		strip(i * data.rays.width, (data.window_hight / 2) - (wall_hight / 2), data.rays.width, wall_hight, 16777092);
	main_dda(i * data.rays.width , 0 ,i * data.rays.width,(data.window_hight / 2) - (wall_hight / 2), 11459583);
	main_dda(i * data.rays.width , (data.window_hight / 2) + (wall_hight / 2) ,i * data.rays.width,data.window_hight, 2101790);
	dda(x, y);
}

void cast_rays()
{
	int col;
	float ray_angle;
	int i;

	i = 0;
	col = 0;
	ray_angle = data.player.rotationAngle - (data.player.fov_angle / 2);
	while (i < data.rays.num)
	{
		check_ray(ray_angle , i);
		ray_angle += data.player.fov_angle / data.rays.num;
		i ++;
	}
}
