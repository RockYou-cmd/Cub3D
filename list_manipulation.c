/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_manipulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 00:18:31 by ael-yamo          #+#    #+#             */
/*   Updated: 2022/10/28 04:04:26 by ael-korc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_list_map	*new(char *str)
{
	t_list_map	*elm;

	elm = malloc(sizeof(t_list_map));
	if (elm == NULL)
		end_game("malloc err");
	elm->line = str;
	elm->next = NULL;
	return (elm);
}

void	add_last(t_list_map **list, char *str)
{
	t_list_map	*elm;
	t_list_map	*tmp;

	if (list == NULL || str == NULL)
		end_game("compiler err");
	tmp = *list;
	elm = new(str);
	if (*list == NULL)
		*list = elm;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = elm;
	}
}

void	remove_end_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	i--;
	while (line[i] == ' ')
		i--;
	line[i + 1] = '\0';
}

t_list_map	*creat_list_map(char *file)
{
	int			fd;
	char		*new_line;
	t_list_map	*list;

	list = NULL;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		end_game("file err");
	new_line = get_next_line(fd);
	while (new_line)
	{
		if (!all_spaces(new_line))
			remove_end_spaces(new_line);
		add_last(&list, new_line);
		new_line = get_next_line(fd);
	}
	close(fd);
	return (list);
}

t_list_map	*delete_node(t_list_map **list, t_list_map *to_delete)
{
	t_list_map	*tmp;

	printf("::%s\n", to_delete->line);
	tmp = *list;
	if (!tmp)
		end_game("somthing wrong with delete");
	if (*list == to_delete)
	{
		*list = to_delete->next;
		return (*list);
	}
	while (tmp->next && tmp->next != to_delete)
		tmp = tmp->next;
	tmp->next = to_delete->next;
	printf("::::%s\n", to_delete->line);
	free(to_delete->line);
	to_delete->next = NULL;
	free(to_delete);
	return (tmp->next);
}
