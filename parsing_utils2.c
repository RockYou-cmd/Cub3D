/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-yamo <ael-yamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 00:54:11 by ael-yamo          #+#    #+#             */
/*   Updated: 2022/10/28 15:36:31 by ael-yamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	check_space(t_line *lines, int index, int i)
{
	if (i != 0 && lines[index].line[i - 1] == '0')
		return (0);
	if (i != (lines[index].len - 1) && \
	(lines[index].line[i + 1] == '0' || is_player(lines[index].line[i + 1])))
		return (0);
	if (index != 0 && lines[index - 1].len >= lines[index].len && \
	lines[index - 1].line[i] == '0')
		return (0);
	if (lines[index].line && lines[index + 1].line && \
	lines[index + 1].len >= lines[index].len && \
	lines[index + 1].line[i] == '0')
		return (0);
	return (1);
}

static void	check_line_utils(t_line *lines, int index, int *i)
{
	while (lines[index].line && lines[index].line[*i] \
	&& lines[index].line[*i] == ' ')
	{
		if (lines[index + 1].line[*i] == '0')
			end_game("map is not closed 3");
		(*i)++;
	}
}

void	check_line(t_line *lines, int index)
{
	int	i;

	i = 0;
	check_line_utils(lines, index, &i);
	if (!lines[index].line[i])
		return ;
	if (lines[index].line[i] != '1' || \
	(lines[index].line[lines[index].len - 1] != '1' \
	&& lines[index].line[lines[index].len - 1] != ' '))
		end_game("map is not closed 4");
	if (index != 0 && (lines[index - 1].len < lines[index].len))
		check_outside(lines[index - 1].len, lines[index].len, lines, index);
	if (index != 0 && (lines[index - 1].len == lines[index].len))
	{
		if (lines[index - 1].line[lines[index].len - 1] != '1')
			end_game("map is not closed 5");
	}
	else
		check_outside(lines[index].len, lines[index - 1].len, lines, index - 1);
}

int	all_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
		{
			return (0);
		}
		i++;
	}
	return (1);
}
