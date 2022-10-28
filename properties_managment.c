/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   properties_managment.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 01:15:03 by ael-yamo          #+#    #+#             */
/*   Updated: 2022/10/28 04:15:25 by ael-korc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	pars_props(t_list_map *list)
{
	int		arr[6];
	char	**prop;
	int		count;
	char	*line;

	count = 6;
	while (count && list)
	{
		line = ft_strtrim(list->line, "\n");
		if (!line)
			end_game("malloc error");
		prop = ft_split(line, ' ');
		if (!prop)
			end_game("malloc error");
		free(line);
		pars_props_utils(prop, &arr);
		free_2d_arr(prop);
		list = list->next;
		count--;
	}
	pars_props_utils2(&arr, count);
}

void	delete_props(t_list_map **list)
{
	int	count;

	count = 6;
	while (count)
	{
		printf("test1\n");
		delete_node(list, *list);
		printf("test2\n");
		count--;
	}
}
