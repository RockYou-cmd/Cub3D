/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 01:58:28 by ael-korc          #+#    #+#             */
/*   Updated: 2022/10/28 01:58:29 by ael-korc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	movement_check(int key)
{
	if (key == RIGHT)
		data.player.twalkDirection = -1;
	if (key == LEFT)
		data.player.twalkDirection = 1;
	if (key == UP)
		data.player.walkDirection = 1;
	if (key == DOWN)
		data.player.walkDirection = -1;
	if (key == TRIGHT)
		data.player.turnDirection = 1;
	if (key == TLEFT)
		data.player.turnDirection = -1;
	if (key == 53)
		exit(1);
	return (0);
}

int	movement2_check(int key)
{
	if (key == RIGHT)
		data.player.twalkDirection = 0;
	if (key == LEFT)
		data.player.twalkDirection = 0;
	if (key == UP)
		data.player.walkDirection = 0;
	if (key == DOWN)
		data.player.walkDirection = 0;
	if (key == TRIGHT)
		data.player.turnDirection = 0;
	if (key == TLEFT)
		data.player.turnDirection = 0;
	return (0);
}

int	movment(void)
{
	if (data.player.twalkDirection
		|| data.player.walkDirection || data.player.turnDirection)
	{
		mlx_destroy_image(data.mlx, data.img);
		update();
	}
	return (0);
}

int	red_cross(void)
{
	mlx_clear_window(data.mlx, data.win);
	mlx_destroy_window(data.mlx, data.win);
	exit(0);
}

int	main(int acc, char **av)
{
	(void) acc;
	init(av);
	data.mlx = mlx_init();
	data.win
		= mlx_new_window(data.mlx, data.window_width, data.window_hight, "cub");
	read_textures();
	game_start();
	mlx_hook(data.win, 2, 1L << 0, movement_check, &data);
	mlx_hook(data.win, 3, 1L << 1, movement2_check, &data);
	mlx_loop_hook(data.mlx, movment, 0);
	mlx_hook(data.win, 17, 0, red_cross, &data);
	mlx_loop(data.mlx);
}
