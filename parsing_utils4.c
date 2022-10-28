/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-yamo <ael-yamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 00:58:13 by ael-yamo          #+#    #+#             */
/*   Updated: 2022/10/28 00:58:14 by ael-yamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_map_elm_utils(t_line *lines, \
t_props *props, int *player, t_index index)
{
	data.player.x = index.i * data.square_size + 15;
	data.player.y = index.index * data.square_size + 15;
	*player = 1;
	(*props).player_l_d = check_player(lines[index.index].line[index.i]);
	lines[index.index].line[index.i] = '0';
}

static void	valid_player(int player)
{
	if (player == -1)
		end_game("no player found");
}

void	check_map_elm(t_line *lines, t_props *props)
{
	t_index	index;
	int		player;

	index.index = 1;
	player = -1;
	while (lines[index.index].line)
	{
		index.i = 0;
		while (lines[index.index].line[index.i] != '\0')
		{
			if (check_player(lines[index.index].line[index.i]) != -1 \
			&& player == -1)
				check_map_elm_utils(lines, props, &player, index);
			else if (check_player(lines[index.index].line[index.i]) != -1 \
			&& player != -1)
				end_game("too many players");
			if (lines[index.index].line[index.i] == ' ' && \
			!check_space(lines, index.index, index.i))
				end_game("map is wrong");
			index.i++;
		}
		index.index++;
	}
	valid_player(player);
}

