#include "cub3d.h"

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
		my_mini_mlx_pixel_put(x, y, 16776960);
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

int hcast(float nextX, float nextY, float hstepx, float hstepy)
{
	while (nextX > 0 && nextX < (data.map.cols * data.square_size) && nextY > 0 && nextY < (data.map.rows * data.square_size))
	{
		if (wall_check(nextX, nextY))
		{
			data.rays.horz_wall_hitx = nextX;
			data.rays.horz_wall_hity = nextY;
			return 1;
		}
		else
		{
			nextX += hstepx;
			nextY += hstepy; 
		}
	}
	return 0;
}
int vcast(float nextX, float nextY, float vstepx, float vstepy)
{
	while (nextX > 0 && nextX < (data.map.cols * data.square_size) && nextY > 0 && nextY < (data.map.rows * data.square_size))
	{
		if (wall_check(nextX, nextY))
		{
			data.rays.vert_wall_hitx = nextX;
			data.rays.vert_wall_hity = nextY;
			return 1;
		}
		else
		{
			nextX += vstepx;
			nextY += vstepy; 
		}
	}
	return 0;
}
void direction_check(float ray_angle)
{
	if (ray_angle > 0 && ray_angle < M_PI)
	{
		data.ud = 0;
	}
	else
	{
		data.ud = 1;
	}
	if (ray_angle < M_PI * 0.5 || ray_angle > M_PI * 1.5)
	{
		data.rl = 1;
	}
	else 
	{
		data.rl = 0;
	}
}

float angleof_ray(float ray_angle)
{
	ray_angle = angle_corrector(ray_angle);
	data.rays.down = 0;
	data.rays.up = 0;
	data.rays.right = 0;
	data.rays.left = 0;
	if (ray_angle >= 0 && ray_angle <= M_PI)
	{
		data.rays.down = 1;
	}
	else //if (ray_angle > M_PI)
	{
		data.rays.up = 1;
	}
	if (ray_angle <= M_PI * 0.5 || ray_angle >= M_PI * 1.5)
	{
		data.rays.right = 1;
	}
	else //if (ray_angle > M_PI * 0.5 && ray_angle < M_PI * 1.5)
	{
		data.rays.left = 1;
	}
	// printf("up : %d | down : %d | right : %d | left : %d\n", data.rays.up, data.rays.down, data.rays.right , data.rays.left);
	direction_check(ray_angle);	
	return (ray_angle);
}


void check_ray(float ray_angle, int i, int d)
{
	float walldistance;
	float wall_hight;
	float hit_distance;
	int x_offset = 0;
	int way = 0;
	int x;
	int y;

	if (horizon_check(ray_angle))
		data.rays.hdistance = distance(data.rays.horz_wall_hitx, data.rays.horz_wall_hity);
	else
		data.rays.hdistance =  INT32_MAX;
	if (vertic_check(ray_angle))
		data.rays.vdistance = distance(data.rays.vert_wall_hitx, data.rays.vert_wall_hity);
	else
		data.rays.vdistance =  INT32_MAX;
	if (data.rays.hdistance <= data.rays.vdistance)
	{
		way = 1;
		hit_distance = data.rays.hdistance;
		// x_offset = (int)data.rays.horz_wall_hitx % data.square_size;
		x_offset = fmod(data.rays.horz_wall_hitx , data.square_size);
		x = data.rays.horz_wall_hitx;
		y = data.rays.horz_wall_hity;
	}
	else
	{
		hit_distance = data.rays.vdistance;
		// x_offset = (int)data.rays.vert_wall_hity % data.square_size;
		x_offset = fmod(data.rays.vert_wall_hity , data.square_size);
		x = data.rays.vert_wall_hitx;
		y = data.rays.vert_wall_hity;
	}
	hit_distance = hit_distance * cos(ray_angle - data.player.rotationAngle);
	walldistance = (data.window_width / 2) / tan(data.player.fov_angle / 2);
	wall_hight = (32 / hit_distance) * walldistance;
	if (d == 3)
		draw3D(wall_hight, i, x_offset, way);
	else
		dda(x, y);
}

void cast_rays(int d)
{
	int col;
	float ray_angle;
	int i;

	i = 0;
	col = 0;
	ray_angle = data.player.rotationAngle - (data.player.fov_angle / 2);
	while (i < data.rays.num)
	{
		check_ray(angleof_ray(ray_angle) , i, d);
		ray_angle += data.player.fov_angle / data.rays.num;
		i ++;
	}
}
