/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 01:58:51 by ael-korc          #+#    #+#             */
/*   Updated: 2022/10/28 02:43:36 by ael-korc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	sum_of_rgb(int r, int g, int b)
{
	return ((65536 * r) + (256 * g) + b);
}

float	distance(float x, float y)
{
	return (sqrt((x - g_data.player.x) * (x - g_data.player.x)
			+ (y - g_data.player.y) * (y - g_data.player.y)));
}

float	angle_corrector(float angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	return (angle);
}

void	dda(float x2, float y2)
{
	float	step;
	float	x;
	float	y;
	float	dx;
	float	dy;

	x = g_data.player.x;
	y = g_data.player.y;
	dx = x2 - x;
	dy = y2 - y;
	if (fabs(dx) > fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	dx /= step;
	dy /= step;
	g_data.index.i = 1;
	while (g_data.index.i <= step)
	{
		my_mini_mlx_pixel_put(x, y, 16776960);
		x += dx;
		y += dy;
		g_data.index.i ++;
	}
}

void	main_dda(float x, float y, float x2, float y2)
{
	float	step;
	float	dx;
	float	dy;
	int		i;
	int		color;

	color = g_data.props.f;
	if (!y)
		color = g_data.props.c;
	dx = x2 - x;
	dy = y2 - y;
	if (fabs(dx) > fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	dx /= step;
	dy /= step;
	i = 1;
	while (i <= step)
	{
		my_main_mlx_pixel_put(x, y, color);
		x += dx;
		y += dy;
		i ++;
	}
}
