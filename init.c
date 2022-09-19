#include "cub3d.h"
void var_update()
{
    int movestep;
    float nextX;
    float nextY;
    data.img = mlx_new_image(data.mlx, data.window_width, data.window_hight);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
    data.player.rotationAngle += data.player.turnDirection * data.player.rotationSpeed;
    data.player.rotationAngle =  angle_corrector(data.player.rotationAngle);
	data.player.move_angle = data.player.rotationAngle - (data.player.fov_angle * 1.5);
    angle_corrector(data.player.move_angle);
    if (data.player.twalkDirection)
    {
        movestep = data.player.twalkDirection * data.player.moveSpeed;
        nextX = data.player.x + cos(data.player.move_angle) * movestep;
        nextY = data.player.y + sin(data.player.move_angle) * movestep;
    }
    else
    {
        movestep = data.player.walkDirection * data.player.moveSpeed;
        nextX = data.player.x + cos(data.player.rotationAngle) * movestep;
        nextY = data.player.y + sin(data.player.rotationAngle) * movestep;
    }
    if (wall_check(nextX, nextY) == 0)
    {
        data.player.x = nextX;
        data.player.y = nextY;
    }
    data.player.walkDirection = 0;
    data.player.twalkDirection = 0;
    data.player.turnDirection = 0;
}
void update()
{
    var_update();
	cast_rays();
	draw();
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);

}

void game_start()
{
    update();
}

void init(char **av)
{
    data.square_size = 32;
    data.map.array = malloc(sizeof(char *));
    read_map(av[1]);
    // data.window_hight = 1900;
    // data.window_width = 2400;
    data.window_hight = data.square_size * data.map.rows;
    data.window_width = data.square_size * data.map.cols;
    data.player.turnDirection = 0;
    data.player.walkDirection = 0;
    data.player.rotationAngle = M_PI / 2;
    data.player.rotationSpeed = 8 * (M_PI / 180);
    data.player.moveSpeed = 10.0;
    // data.player.x = data.window_width/2;
    // data.player.y = data.window_hight/2;
    data.player.fov_angle = 60 * (M_PI / 180);
    data.rays.num = data.window_width;
    data.rays.width = 1;
}
 
  