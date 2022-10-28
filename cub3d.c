/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 01:58:28 by ael-korc          #+#    #+#             */
/*   Updated: 2022/10/28 03:44:11 by ael-korc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	movement_check(int key)
{
	if (key == RIGHT)
		g_data.player.twalk_direction = -1;
	if (key == LEFT)
		g_data.player.twalk_direction = 1;
	if (key == UP)
		g_data.player.walk_direction = 1;
	if (key == DOWN)
		g_data.player.walk_direction = -1;
	if (key == TRIGHT)
		g_data.player.turn_direction = 1;
	if (key == TLEFT)
		g_data.player.turn_direction = -1;
	if (key == 53)
		exit(1);
	return (0);
}

int	movement2_check(int key)
{
	if (key == RIGHT)
		g_data.player.twalk_direction = 0;
	if (key == LEFT)
		g_data.player.twalk_direction = 0;
	if (key == UP)
		g_data.player.walk_direction = 0;
	if (key == DOWN)
		g_data.player.walk_direction = 0;
	if (key == TRIGHT)
		g_data.player.turn_direction = 0;
	if (key == TLEFT)
		g_data.player.turn_direction = 0;
	return (0);
}

int	movment(void)
{
	if (g_data.player.twalk_direction
		|| g_data.player.walk_direction || g_data.player.turn_direction)
	{
		mlx_destroy_image(g_data.mlx, g_data.img);
		update();
	}
	return (0);
}

int	red_cross(void)
{
	mlx_clear_window(g_data.mlx, g_data.win);
	mlx_destroy_window(g_data.mlx, g_data.win);
	exit(0);
}

int	main(int acc, char **av)
{
	(void) acc;
	init(av);
	g_data.mlx = mlx_init();
	g_data.win = mlx_new_window(g_data.mlx,
			g_data.window_width, g_data.window_hight, "cub");
	read_textures();
	game_start();
	mlx_hook(g_data.win, 2, 1L << 0, movement_check, &g_data);
	mlx_hook(g_data.win, 3, 1L << 1, movement2_check, &g_data);
	mlx_loop_hook(g_data.mlx, movment, 0);
	mlx_hook(g_data.win, 17, 0, red_cross, &g_data);
	mlx_loop(g_data.mlx);
}
