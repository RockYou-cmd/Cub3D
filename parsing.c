/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-yamo <ael-yamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 00:31:11 by ael-yamo          #+#    #+#             */
/*   Updated: 2022/10/28 15:27:39 by ael-yamo         ###   ########.fr       */
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
		if (g_data.map.cols < lines[i].len)
			g_data.map.cols = lines[i].len;
		i++;
	}
	g_data.map.rows = i;
}

void	line_to_str(t_line *lines)
{
	int	i;
	int	len;

	g_data.map.rows = -1;
	g_data.map.cols = -1;
	width_height(lines);
	if (g_data.map.cols == -1 || g_data.map.rows == -1)
		end_game("map 69");
	g_data.map.array = malloc(sizeof(char *) * (g_data.map.rows + 1));
	if (!lines)
		end_game("map 69");
	i = 0;
	len = 0;
	while (lines[i].line)
	{
		g_data.map.array[i] = lines[i].line;
		i++;
	}
	g_data.map.array[i] = NULL;
	free(lines);
	lines = NULL;
}

void	free_list(t_list_map **list)
{
	t_list_map	*tmp;

	tmp = *list;
	while (tmp){
		tmp = delete_node(list, tmp);
	}
}

void	print_list_map(t_list_map **tmp)
{
	t_list_map *list = *tmp;
	while (list)
	{
		printf("%s",list->line);
		list = list->next;
	}
}

void	init_map(char **av)
{
	t_list_map	*list;
	t_line		*lines;

	check_extention(av[1], ".cub");
	list = creat_list_map(av[1]);
	remove_empty_lines(&list);
	pars_props(list);
	g_data.props.f = sum_of_rgb(g_data.props.f_rgb[0], \
	g_data.props.f_rgb[1], g_data.props.f_rgb[2]);
	g_data.props.c = sum_of_rgb(g_data.props.c_rgb[0], \
	g_data.props.c_rgb[1], g_data.props.c_rgb[2]);
	g_data.props.player_l_d = M_PI / 2;
	delete_props(&list);
	lines = list_to_arr(list);
	free_list(&list);
	map_is_closed(lines);
	check_map_elm(lines, &g_data.props);
	line_to_str(lines);
	free_list(&list);
}
