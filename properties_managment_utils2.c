/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   properties_managment_utils2.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 01:21:26 by ael-yamo          #+#    #+#             */
/*   Updated: 2022/10/28 04:15:35 by ael-korc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_color(int (*arr)[6], int n, int (*colors)[3], char **str)
{
	char	**colors_str;
	int		count;

	colors_str = get_clr_str(str);
	ft_striteri2(colors_str, check_digit);
	count = 0;
	while (colors_str[count] != NULL)
		count++;
	if (count != 3)
		end_game("colors problem");
	(*arr)[n] = 1;
	(*colors)[0] = ft_atoi(colors_str[0]);
	(*colors)[1] = ft_atoi(colors_str[1]);
	(*colors)[2] = ft_atoi(colors_str[2]);
	free_2d_arr(colors_str);
	count = 0;
	while (count < 3)
	{
		if ((*colors)[count] > 255 || (*colors)[count] < 0)
			end_game("colors out of range");
		count++;
	}
}

static int	count_prop(char **prop)
{
	int	i;

	i = 0;
	if (!prop)
		return (0);
	while (prop[i])
	{
		i++;
	}
	return (i);
}

void	free_2d_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	pars_props_utils(char **prop, int (*arr)[6])
{
	if (count_prop(prop) == 2 && ft_strcmp(prop[0], "NO") == 0)
		g_data.props.no = fill_wall(arr, NO, prop[1]);
	else if (count_prop(prop) == 2 && ft_strcmp(prop[0], "SO") == 0)
		g_data.props.so = fill_wall(arr, SO, prop[1]);
	else if (count_prop(prop) == 2 && ft_strcmp(prop[0], "WE") == 0)
		g_data.props.we = fill_wall(arr, WE, prop[1]);
	else if (count_prop(prop) == 2 && ft_strcmp(prop[0], "EA") == 0)
		g_data.props.ea = fill_wall(arr, EA, prop[1]);
	else if (count_prop(prop) >= 2 && ft_strcmp(prop[0], "F") == 0)
		fill_color(arr, F, &g_data.props.f_rgb, prop);
	else if (count_prop(prop) >= 2 && ft_strcmp(prop[0], "C") == 0)
		fill_color(arr, C, &g_data.props.c_rgb, prop);
}

void	pars_props_utils2(int (*arr)[6], int count)
{
	int	i;

	i = 0;
	while (!count && (*arr)[i] == 1)
	{
		i++;
	}
	if (i != 6)
		end_game("map");
}
