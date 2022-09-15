#include "cub3d.h"


int movment(int key)
{    
    if (key == RIGHT)
        data.player.twalkDirection = -1;
    if (key == LEFT)
        data.player.twalkDirection = 1;
    if (key == UP)
        data.player.walkDirection = 1;
    if (key == DOWN)
        data.player.walkDirection = -1;
    if (key == 53 )
        exit(1);
    if (key == TRIGHT)
        data.player.turnDirection = 1;
    if (key == TLEFT)
        data.player.turnDirection = -1;
    update();
    return 0;
}



int main(int acc, char **av)
{
    (void) acc;
	init(av);
    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, data.window_width, data.window_hight, "cub3d");
    game_start(&data);
    mlx_hook(data.win, 2, 1L<<0, movment, &data);
    mlx_loop(data.mlx);
}