/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 01:58:25 by ael-korc          #+#    #+#             */
/*   Updated: 2022/10/28 18:03:00 by ael-korc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	horizon_check(float ray_angle)
{
	float	nextx;
	float	nexty;
	float	hstepx;
	float	hstepy;

	g_data.rays.first_intersectiony
		= floor(g_data.player.y / g_data.square_size)
		* g_data.square_size;
	if (g_data.rays.down)
		g_data.rays.first_intersectiony += g_data.square_size;
	g_data.rays.first_intersectionx = g_data.player.x
		+(g_data.rays.first_intersectiony - g_data.player.y) / tan(ray_angle);
	hstepy = g_data.square_size;
	if (g_data.rays.up)
		hstepy *= -1;
	hstepx = g_data.square_size / tan(ray_angle);
	if (g_data.rays.left && hstepx > 0)
		hstepx *= -1;
	if (g_data.rays.right && hstepx < 0)
		hstepx *= -1;
	nextx = g_data.rays.first_intersectionx;
	nexty = g_data.rays.first_intersectiony;
	if (g_data.rays.up)
		nexty --;
	return (hcast(nextx, nexty, hstepx, hstepy));
}

int	vertic_check(float ray_angle)
{
	float	nextx;
	float	nexty;
	float	vstepx;
	float	vstepy;

	g_data.rays.first_intersectionx
		= floor(g_data.player.x / g_data.square_size)
		* g_data.square_size;
	if (g_data.rays.right)
		g_data.rays.first_intersectionx += g_data.square_size;
	g_data.rays.first_intersectiony = g_data.player.y
		+ (g_data.rays.first_intersectionx - g_data.player.x) * tan(ray_angle);
	vstepx = g_data.square_size;
	if (g_data.rays.left)
		vstepx *= -1;
	vstepy = g_data.square_size * tan(ray_angle);
	if (g_data.rays.up && vstepy > 0)
		vstepy *= -1;
	if (g_data.rays.down && vstepy < 0)
		vstepy *= -1;
	nextx = g_data.rays.first_intersectionx;
	nexty = g_data.rays.first_intersectiony;
	if (g_data.rays.left)
		nextx --;
	return (vcast(nextx, nexty, vstepx, vstepy));
}

int	wall_check(float x, float y)
{
	int	col;
	int	row;

	col = floor(x / g_data.square_size);
	row = floor(y / g_data.square_size);

	if (g_data.map.array[row] && col < (int)ft_strlen(g_data.map.array[row])
		&& g_data.map.array[row][col] == '0')
		return (0);
	else
		return (1);
}

float	implement(float hit_distance, float ray_angle)
{
	float	walldistance;
	float	wall_height;

	hit_distance = hit_distance * cos(ray_angle - g_data.player.r_angle);
	walldistance = (g_data.window_width / 2) / tan(g_data.player.fov_angle / 2);
	wall_height = (32 / hit_distance) * walldistance;
	return (wall_height);
}

void	check_ray(float ray_angle, int i)
{
	float	hit_distance;
	int		way;

	way = 0;
	if (horizon_check(ray_angle))
		g_data.rays.hdistance
			= distance(g_data.rays.horz_wall_hitx, g_data.rays.horz_wall_hity);
	if (vertic_check(ray_angle))
		g_data.rays.vdistance
			= distance(g_data.rays.vert_wall_hitx, g_data.rays.vert_wall_hity);
	if (g_data.rays.hdistance <= g_data.rays.vdistance)
	{
		way = 1;
		hit_distance = g_data.rays.hdistance;
		g_data.rays.x_offset
			= fmod(g_data.rays.horz_wall_hitx, g_data.square_size);
	}
	else
	{
		hit_distance = g_data.rays.vdistance;
		g_data.rays.x_offset
			= fmod(g_data.rays.vert_wall_hity, g_data.square_size);
	}
	draw3d(implement(hit_distance, ray_angle), i, way);
}
