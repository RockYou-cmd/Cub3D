#include "cub3d.h"

int horizon_check(float ray_angle)
{
	float nextX;
	float nextY;
	float hstepx;
	float hstepy;
			data.rays.hhited = 0;
	// printf("right : %d | left %d | up : %d down : %d | angle : %f\n",data.rays.right, data.rays.left, data.rays.up, data.rays.down, ray_angle);
	data.rays.first_intersectionY = floor(data.player.y / data.square_size) * data.square_size;
	if(data.rays.down)
		data.rays.first_intersectionY += data.square_size;
	data.rays.first_intersectionX = data.player.x + (data.rays.first_intersectionY - data.player.y) / tan(ray_angle);
	hstepy = data.square_size;
	if (data.rays.up) 
		hstepy *= -1;
	hstepx = data.square_size / tan(ray_angle);
	if (data.rays.left && hstepx > 0)
		hstepx *= -1;
	if (data.rays.right && hstepx < 0)
		hstepx *= -1;
	nextX = data.rays.first_intersectionX;
	nextY = data.rays.first_intersectionY;
	if (data.rays.up)
		nextY --;
	while (nextX > 0 && nextX < data.window_width && nextY > 0 && nextY < data.window_hight)
	{
		if (wall_check(nextX, nextY))
		{
			data.rays.horz_wall_hitx = nextX;
			data.rays.horz_wall_hity = nextY;
			data.rays.hhited = 1;
			break;
		}
		else
		{
			nextX += hstepx;
			nextY += hstepy; 
		}
	}
	// return (hcast(data.rays.first_intersectionX, data.rays.first_intersectionY));
	return 0;
}

int vertic_check(float ray_angle)
{
	float nextX;
	float nextY;
	float vstepx;
	float vstepy; 

	data.rays.vhited = 0;
	data.rays.first_intersectionX = floor(data.player.x / data.square_size) * data.square_size;
	if(data.rays.right)
		data.rays.first_intersectionX += data.square_size;
	data.rays.first_intersectionY = data.player.y + (data.rays.first_intersectionX - data.player.x) * tan(ray_angle);
	vstepx = data.square_size;
	if (data.rays.left)
		vstepx *= -1;
	vstepy = data.square_size * tan(ray_angle);
	if (data.rays.up && vstepy > 0)
		vstepy *= -1;
	if (data.rays.down && vstepy < 0)
		vstepy *= -1;
	nextX = data.rays.first_intersectionX;
	nextY = data.rays.first_intersectionY;
	if (data.rays.left)
		nextX --;
	while (nextX > 0 && nextX < data.window_width && nextY > 0 && nextY < data.window_hight)
	{
		if (wall_check(nextX, nextY))
		{
			data.rays.vert_wall_hitx = nextX;
			data.rays.vert_wall_hity = nextY;
			data.rays.vhited = 1;
			break;
		}
		else
		{
			nextX += vstepx;
			nextY += vstepy; 
		}
	}
	return 0;

}


int wall_check(float x, float y)
{
    int col;
    int row;

    col = floor(x / data.square_size);
	row = floor(y / data.square_size);
    if (data.map.array[row][col] && data.map.array[row][col] == '0')
		return 0;
	else
		return 1;
}