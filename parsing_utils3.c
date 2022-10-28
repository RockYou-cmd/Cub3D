/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-yamo <ael-yamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 00:55:46 by ael-yamo          #+#    #+#             */
/*   Updated: 2022/10/28 00:56:06 by ael-yamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_first_line(t_line *lines)
{
	int	i;
	int	j;

	i = 0;
	while (lines[i].line && all_spaces(lines[i].line))
		i++;
	if (lines[i].line == NULL)
		end_game("map is empty");
	j = 0;
	while (lines[i].line[j] != '\0' && lines[i].line[j] != '\n')
	{
		if (lines[i].line[j] != '1' && lines[i].line[j] != ' ')
			end_game("map is not closed 6");
		if (lines[i].line[j] == ' ')
		{
			if (lines[i + 1].line && lines[i + 1].line[j] == '0')
				end_game("map is not closed 7");
		}
		j++;
	}
}

void	check_last_line(t_line *lines, int i)
{
	int	j;

	j = 0;
	while (lines[i].line[j])
	{
		if (lines[i].line[j] != '1' && lines[i].line[j] != ' ')
			end_game("map is not closed 8");
		if (lines[i].line[j] == ' ')
		{
			if (lines[i - 1].line && lines[i].line[j] == '0')
				end_game("map is not closed 9");
		}
		j++;
	}
}

void	map_is_closed(t_line *lines)
{
	int	index;

	index = 1;
	check_first_line(lines);
	if (lines[index].line)
	{
		while (lines[index + 1].line)
		{
			if (ft_strcmp(lines[index].line, "\n") == 0)
				return ;
			check_line(lines, index);
			index++;
		}
		check_last_line(lines, index);
	}
}

int	check_player(char c)
{
	if (c == 'N')
		return (NO);
	if (c == 'S')
		return (SO);
	if (c == 'W')
		return (WE);
	if (c == 'E')
		return (EA);
	if (c != '1' && c != '0' && c != ' ')
		end_game("there is an outside character");
	return (-1);
}
