/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 01:58:40 by ael-korc          #+#    #+#             */
/*   Updated: 2022/10/28 02:07:38 by ael-korc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	var_update(int mp, float nextX, float nextY)
{
	if (data.player.twalkDirection)
	{
		mp = data.player.twalkDirection * (data.player.moveSpeed + 20);
		nextX = data.player.x + cos(data.player.move_angle) * mp;
		nextY = data.player.y + sin(data.player.move_angle) * mp;
		if (!wall_check(nextX, nextY))
		{
			mp = data.player.twalkDirection * (data.player.moveSpeed);
			data.player.x = data.player.x + cos(data.player.move_angle) * mp;
			data.player.y = data.player.y + sin(data.player.move_angle) * mp;
		}
	}
	else if (data.player.walkDirection)
	{
		mp = data.player.walkDirection * (data.player.moveSpeed + 20);
		nextX = data.player.x + cos(data.player.rotationAngle) * mp;
		nextY = data.player.y + sin(data.player.rotationAngle) * mp;
		if (!wall_check(nextX, nextY))
		{
			mp = data.player.walkDirection * (data.player.moveSpeed);
			data.player.x = data.player.x + cos(data.player.rotationAngle) * mp;
			data.player.y = data.player.y + sin(data.player.rotationAngle) * mp;
		}
	}
}

void	update(void)
{
	mlx_clear_window(data.mlx, data.win);
	data.img = mlx_new_image(data.mlx, data.window_width, data.window_hight);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel,
			&data.length, &data.endian);
	data.player.rotationAngle += angle_corrector(data.player.turnDirection
			* data.player.rotationSpeed);
	data.player.move_angle
		= data.player.rotationAngle - (data.player.fov_angle * 1.5);
	var_update(0, 0, 0);
	cast_rays(3);
	draw2d();
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
}

void	game_start(void)
{
	update();
}

void	init(char **av)
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
