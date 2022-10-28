/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-yamo <ael-yamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 00:50:25 by ael-yamo          #+#    #+#             */
/*   Updated: 2022/10/28 15:08:15 by ael-yamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	end_game(char *error_message)
{
	printf("\033[1;31m");
	if (error_message)
		exit(printf("Error\n%s\n", error_message));
	if (!error_message)
	{
		printf("\033[0;36m");
		printf("\n░▒▓█►─═  ＧＡＭＥ ＣＬＯＳＥＤ ＳＵＣＣＥＳＦＵＬＬＹ ═─◄█▓▒░\n");
		exit(0);
	}
}

int	count_list_elms(t_list_map *list)
{
	int	count;
	int	new_line;

	new_line = 0;
	if (list == NULL)
		return (0);
	count = 1;
	while (list != NULL)
	{
		if (ft_strcmp(list->line, "\n") == 0)
			new_line = 1;
		else
		{
			if (new_line)
				end_game("map is broken");
		}
		list = list->next;
		count++;
	}
	return (count);
}

char	*ft_strdup_n(const char *s1)
{
	int		i;
	int		len;
	char	*cpy;

	i = 0;
	len = 0;
	while (s1[len] != 0)
		len++;
	cpy = malloc((len + 1) * sizeof(char));
	if (cpy == NULL)
		return (NULL);
	while (s1[i] != 0 && s1[i] != '\n')
	{
		cpy[i] = s1[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

t_line	*list_to_arr(t_list_map *list)
{
	t_line	*lines;
	int		line_numbers;
	int		i;

	line_numbers = count_list_elms(list);
	if (line_numbers == 0)
		end_game("map is empty");
	lines = malloc(sizeof(t_line) * (line_numbers));
	if (!lines)
		end_game("malloc failed");
	i = 0;
	while (list && ft_strcmp(list->line, "\n"))
	{
		lines[i].line = ft_strdup_n(list->line);
		if (!lines[i].line)
			end_game("strdup err");
		lines[i].len = ft_strlen(lines[i].line);
		list = list->next;
		i++;
	}
	lines[i].line = NULL;
	return (lines);
}

void	check_outside(int start, int end, t_line *lines, int index)
{
	while (start < end)
	{
		if (lines[index].line[start] == '0')
			end_game("map not closed 1");
		if (lines[index].line[start] == ' ' && \
		(lines[index + 1].len >= lines[index].len && \
		lines[index + 1].line[start] == '0'))
			end_game("map not closed 2");
		start++;
	}
}
