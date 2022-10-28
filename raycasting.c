/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 01:58:49 by ael-korc          #+#    #+#             */
/*   Updated: 2022/10/28 02:36:19 by ael-korc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	hcast(float nextX, float nextY, float hstepx, float hstepy)
{
	while (nextX > 0 && nextX < (g_data.map.cols * g_data.square_size)
		&& nextY > 0 && nextY < (g_data.map.rows * g_data.square_size))
	{
		if (wall_check(nextX, nextY))
		{
			g_data.rays.horz_wall_hitx = nextX;
			g_data.rays.horz_wall_hity = nextY;
			return (1);
		}
		else
		{
			nextX += hstepx;
			nextY += hstepy;
		}
	}
	return (0);
}

int	vcast(float nextX, float nextY, float vstepx, float vstepy)
{
	while (nextX > 0 && nextX < (g_data.map.cols * g_data.square_size)
		&& nextY > 0 && nextY < (g_data.map.rows * g_data.square_size))
	{
		if (wall_check(nextX, nextY))
		{
			g_data.rays.vert_wall_hitx = nextX;
			g_data.rays.vert_wall_hity = nextY;
			return (1);
		}
		else
		{
			nextX += vstepx;
			nextY += vstepy;
		}
	}
	return (0);
}

void	direction_check(float ray_angle)
{
	if (ray_angle > 0 && ray_angle < M_PI)
		g_data.ud = 0;
	else
		g_data.ud = 1;
	if (ray_angle < M_PI * 0.5 || ray_angle > M_PI * 1.5)
		g_data.rl = 1;
	else
		g_data.rl = 0;
}

float	angleof_ray(float ray_angle)
{
	ray_angle = angle_corrector(ray_angle);
	g_data.rays.down = 0;
	g_data.rays.up = 0;
	g_data.rays.right = 0;
	g_data.rays.left = 0;
	if (ray_angle >= 0 && ray_angle <= M_PI)
	{
		g_data.rays.down = 1;
	}
	else
	{
		g_data.rays.up = 1;
	}
	if (ray_angle <= M_PI * 0.5 || ray_angle >= M_PI * 1.5)
	{
		g_data.rays.right = 1;
	}
	else
	{
		g_data.rays.left = 1;
	}
	direction_check(ray_angle);
	return (ray_angle);
}

void	cast_rays(int d)
{
	int		col;
	float	ray_angle;
	int		i;

	(void) d;
	i = 0;
	col = 0;
	ray_angle = g_data.player.r_angle - (g_data.player.fov_angle / 2);
	while (i < g_data.rays.num)
	{
		g_data.rays.hdistance = INT32_MAX;
		g_data.rays.vdistance = INT32_MAX;
		check_ray(angleof_ray(ray_angle), i);
		ray_angle += g_data.player.fov_angle / g_data.rays.num;
		i ++;
	}
}
