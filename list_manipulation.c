#include "cub3d.h"

t_list_map *new(char *str)
{
	t_list_map *elm;
	elm = malloc(sizeof(t_list_map));
	if (elm == NULL)
		end_game("malloc err");
	elm->line = str;
	elm->next = NULL;
	return (elm);
}

void	add_last(t_list_map **list, char *str)
{
	t_list_map *elm;
	t_list_map *tmp;

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

t_list_map	*creat_list_map(char *file)
{
	int fd;
	char *whole_map;
	char *new_line;
	t_list_map *list;
	// char **mapfile;
	list = NULL;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		end_game("file err");
	whole_map = ft_strdup("");
	new_line = get_next_line(fd);
	while (new_line)
	{
		add_last(&list, new_line);
		new_line = get_next_line(fd);
	}
	close(fd);
	return list;
}

t_list_map *delete_node(t_list_map **list, t_list_map *to_delete)
{
	t_list_map *tmp;
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
	to_delete->next = NULL;
	free(to_delete);
	return (tmp->next);
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