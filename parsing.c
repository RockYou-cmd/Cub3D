/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-yamo <ael-yamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 00:31:11 by ael-yamo          #+#    #+#             */
/*   Updated: 2022/10/28 00:58:00 by ael-yamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	width_height(t_line *lines)
{
	int	i;

	if (!lines)
		return ;
	i = 0;
	while (lines[i].line)
	{
		if (data.map.cols < lines[i].len)
			data.map.cols = lines[i].len;
		i++;
	}
	data.map.rows = i;
}

void	line_to_str(t_line *lines)
{
	int	i;
	int	len;

	data.map.rows = -1;
	data.map.cols = -1;
	width_height(lines);
	if (data.map.cols == -1 || data.map.rows == -1)
		end_game("map 69");
	data.map.array = malloc(sizeof(char *) * (data.map.rows + 1));
	if (!lines)
		end_game("map 69");
	i = 0;
	len = 0;
	while (lines[i].line)
	{
		data.map.array[i] = lines[i].line;
		i++;
	}
	data.map.array[i] = NULL;
	free(lines);
	lines = NULL;
}

void	free_list(t_list_map **list)
{
	t_list_map	*tmp;

	tmp = *list;
	while (tmp)
		tmp = delete_node(list, tmp);
}

void	init_map(char **av)
{
	t_list_map	*list;
	t_line		*lines;

	check_extention(av[1], ".cub");
	list = creat_list_map(av[1]);
	remove_empty_lines(&list);
	pars_props(list);
	data.props.f = sum_of_rgb(data.props.f_rgb[0], \
	data.props.f_rgb[1], data.props.f_rgb[2]);
	data.props.c = sum_of_rgb(data.props.c_rgb[0], \
	data.props.c_rgb[1], data.props.c_rgb[2]);
	data.props.player_l_d = M_PI / 2;
	delete_props(&list);
	lines = list_to_arr(list);
	free_list(&list);
	map_is_closed(lines);
	check_map_elm(lines, &data.props);
	line_to_str(lines);
	free_list(&list);
}
