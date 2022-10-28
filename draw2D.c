/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2D.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 01:58:32 by ael-korc          #+#    #+#             */
/*   Updated: 2022/10/28 02:32:39 by ael-korc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_main_mlx_pixel_put(int x, int y, int color)
{
	char	*dst;

	if (x >= g_data.window_width
		|| x <= 0 || y >= g_data.window_hight || y <= 0)
		return ;
	dst = g_data.addr + (y * g_data.length + x * (g_data.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	my_mini_mlx_pixel_put(int x, int y, int color)
{
	char	*dst;

	x /= 4;
	y /= 4;
	if (x > (g_data.player.x / 4) + 100 || x < (g_data.player.x / 4) - 100
		|| y > (g_data.player.y / 4) + 100 || y < (g_data.player.y / 4) - 100)
		return ;
	x -= (g_data.player.x / 4) - 100;
	y -= (g_data.player.y / 4) - 100;
	dst = g_data.addr + (y * g_data.length + x * (g_data.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	player(void)
{
	float	r;
	float	x;
	float	y;
	float	angle;

	r = 10;
	while (r >= 0)
	{
		angle = 0;
		while (angle <= 10)
		{
			x = r * cos(angle) + g_data.player.x;
			y = r * sin(angle) + g_data.player.y;
			my_mini_mlx_pixel_put(x, y, 16776960);
			angle += 0.1;
		}
		r -= 1;
	}
	x = g_data.player.x + (cos(g_data.player.r_angle) * 50);
	y = g_data.player.y + (sin(g_data.player.r_angle) * 50);
	dda(x, y);
}

void	square_drawing(int ix, int iy, int color)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y <= g_data.square_size - 2)
	{
		x = 0;
		while (x <= g_data.square_size - 2)
		{
			my_mini_mlx_pixel_put(ix + x, iy + y, color);
			x ++;
		}
		y ++;
	}
}

void	draw2d(void)
{
	int	iy;
	int	ix;

	ix = 0;
	iy = 0;
	while (iy < g_data.map.rows)
	{
		ix = 0;
		while (g_data.map.array[iy][ix])
		{
			if (g_data.map.array[iy][ix] && g_data.map.array[iy][ix] == '1')
				square_drawing(ix * g_data.square_size, iy * g_data.square_size,
					15601958);
			else if (g_data.map.array[iy][ix]
				&& g_data.map.array[iy][ix] == '0')
				square_drawing(ix * g_data.square_size, iy * g_data.square_size,
					2497294);
			ix ++;
		}
		iy ++;
	}
	player();
}
