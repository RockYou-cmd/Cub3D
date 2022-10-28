/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 01:58:40 by ael-korc          #+#    #+#             */
/*   Updated: 2022/10/28 02:35:43 by ael-korc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	var_update(int ms, float nextX, float nextY)
{
	if (g_data.player.twalk_direction)
	{
		ms = g_data.player.twalk_direction * (g_data.player.move_speed + 20);
		nextX = g_data.player.x + cos(g_data.player.mv_angl) * ms;
		nextY = g_data.player.y + sin(g_data.player.mv_angl) * ms;
		if (!wall_check(nextX, nextY))
		{
			ms = g_data.player.twalk_direction * (g_data.player.move_speed);
			g_data.player.x = g_data.player.x + cos(g_data.player.mv_angl) * ms;
			g_data.player.y = g_data.player.y + sin(g_data.player.mv_angl) * ms;
		}
	}
	else if (g_data.player.walk_direction)
	{
		ms = g_data.player.walk_direction * (g_data.player.move_speed + 20);
		nextX = g_data.player.x + cos(g_data.player.r_angle) * ms;
		nextY = g_data.player.y + sin(g_data.player.r_angle) * ms;
		if (!wall_check(nextX, nextY))
		{
			ms = g_data.player.walk_direction * (g_data.player.move_speed);
			g_data.player.x = g_data.player.x + cos(g_data.player.r_angle) * ms;
			g_data.player.y = g_data.player.y + sin(g_data.player.r_angle) * ms;
		}
	}
}

void	update(void)
{
	mlx_clear_window(g_data.mlx, g_data.win);
	g_data.img = mlx_new_image(g_data.mlx,
			g_data.window_width, g_data.window_hight);
	g_data.addr = mlx_get_data_addr(g_data.img, &g_data.bits_per_pixel,
			&g_data.length, &g_data.endian);
	g_data.player.r_angle += angle_corrector(g_data.player.turn_direction
			* g_data.player.r_speed);
	g_data.player.mv_angl
		= g_data.player.r_angle - (g_data.player.fov_angle * 1.5);
	var_update(0, 0, 0);
	cast_rays(3);
	draw2d();
	mlx_put_image_to_window(g_data.mlx, g_data.win, g_data.img, 0, 0);
}

void	game_start(void)
{
	update();
}

void	init(char **av)
{
	g_data.square_size = 32;
	init_map(av);
	g_data.window_hight = 1100;
	g_data.window_width = 1620;
	g_data.texture_size = g_data.square_size;
	g_data.player.r_angle = M_PI / 2;
	g_data.player.r_speed = 3 * (M_PI / 180);
	g_data.player.move_speed = 5.0;
	g_data.player.fov_angle = 60 * (M_PI / 180);
	g_data.rays.num = g_data.window_width;
	g_data.rays.width = 1;
}
