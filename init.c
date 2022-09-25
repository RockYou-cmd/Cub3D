#include "cub3d.h"


void var_update()
{
	int movestep;
	float nextX;
	float nextY;
	char dd = 'v';
	char ud = 'v';
	data.img = mlx_new_image(data.mlx, data.window_width, data.window_hight);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	data.player.rotationAngle += data.player.turnDirection * data.player.rotationSpeed;
	data.player.rotationAngle =  angle_corrector(data.player.rotationAngle);
	if (data.player.walkDirection && data.player.rotationAngle >= 0 && data.player.rotationAngle <= (M_PI/2))
		dd = 'r';
	else if (data.player.walkDirection && data.player.rotationAngle <= M_PI && data.player.rotationAngle >= (M_PI/2))
		dd = 'l';
	if (data.player.walkDirection && data.player.rotationAngle >= M_PI && data.player.rotationAngle <= (M_PI*1.5))
		ud = 'l';
	else if (data.player.walkDirection && data.player.rotationAngle <= (2 * M_PI) && data.player.rotationAngle >= (M_PI*1.5))
		ud = 'r';
	data.player.move_angle = data.player.rotationAngle - (data.player.fov_angle * 1.5);
	angle_corrector(data.player.move_angle);
	if (data.player.twalkDirection)
	{
		movestep = data.player.twalkDirection * data.player.moveSpeed;
		nextX = data.player.x + cos(data.player.move_angle) * movestep;
		nextY = data.player.y + sin(data.player.move_angle) * movestep;
	}
	else if (data.player.walkDirection)
	{
		movestep = data.player.walkDirection * data.player.moveSpeed;
		nextX = data.player.x + cos(data.player.rotationAngle) * movestep;
		nextY = data.player.y + sin(data.player.rotationAngle) * movestep;
	}
	// printf("dow_r : %d dow_l : %d up_l : %d up_r : %d\n",dow_r, dow_l, up_l, up_r);
	if (data.player.walkDirection && !wall_check(nextX, nextY) && ((dd = 'r' && !wall_check(nextX + 15, nextY + 15)) || (dd = 'l' && !wall_check(nextX - 15, nextY + 15)) || (ud == 'l' && !wall_check(nextX - 15, nextY - 15)) || (ud == 'r' && !wall_check(nextX + 15, nextY - 15))))
	// if (data.player.walkDirection && !wall_check(nextX, nextY) && (dd = 'r' && !wall_check(nextX + 15, nextY + 15)))
	{
		data.player.x = nextX;
		data.player.y = nextY;
	}
	dd = 'v';
	ud = 'v';
	if (data.player.twalkDirection && data.player.rotationAngle - (data.player.fov_angle * 1.5)  > 0 && data.player.rotationAngle - (data.player.fov_angle * 1.5) < (M_PI/2))
		dd = 'r';
	if (data.player.twalkDirection && data.player.rotationAngle - (data.player.fov_angle * 1.5) < M_PI && data.player.rotationAngle - (data.player.fov_angle * 1.5) > (M_PI/2))
		dd = 'l';
	if (data.player.twalkDirection && data.player.rotationAngle - (data.player.fov_angle * 1.5) > M_PI && data.player.rotationAngle - (data.player.fov_angle * 1.5) < (M_PI*1.5))
		ud = 'l';
	if (data.player.twalkDirection && data.player.rotationAngle - (data.player.fov_angle * 1.5) < (2 * M_PI) && data.player.rotationAngle - (data.player.fov_angle * 1.5) > (M_PI*1.5))
		ud = 'r';
	if (data.player.twalkDirection && !wall_check(nextX, nextY) && (dd = 'r' && !wall_check(nextX + 8, nextY + 8)))
	{
		data.player.x = nextX;
		data.player.y = nextY;
	}
	if (data.player.twalkDirection && !wall_check(nextX, nextY) && (dd = 'l' && !wall_check(nextX - 8, nextY + 8)))
	{
		data.player.x = nextX;
		data.player.y = nextY;
	}
	if (data.player.twalkDirection && !wall_check(nextX, nextY) && ud == 'l' && !wall_check(nextX - 8, nextY - 8))
	{
		data.player.x = nextX;
		data.player.y = nextY;
	}
	if (data.player.twalkDirection && !wall_check(nextX, nextY) && ud == 'r' && !wall_check(nextX + 8, nextY - 8))
	{
		data.player.x = nextX;
		data.player.y = nextY;
	}
}
void update()
{
	mlx_clear_window(data.mlx, data.win);
	var_update();
	cast_rays(3);
	draw2D();
	// cast_rays(2);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);

}

void game_start()
{
	update();
}

void init(char **av)
{
	data.square_size = 32;
	init_map(av);
	data.window_hight = 1100;
	data.window_width = 1620;
	data.texture_size = data.square_size;
	data.player.rotationAngle = M_PI / 2;
	data.player.rotationSpeed = 3 * (M_PI / 180);
	data.player.moveSpeed = 5.0;
	data.player.fov_angle = 60 * (M_PI / 180);
	data.rays.num = data.window_width;
	data.rays.width = 1;
}
