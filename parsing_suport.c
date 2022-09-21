#include "cub3d.h"

void remove_empty_lines(t_list_map **list)
{
	t_list_map *tmp;
	int count = 7;

	tmp = *list;	
	while (tmp && count)
	{
		if(tmp->line[0] == '\n' || all_spaces(ft_strtrim(tmp->line, "\n")))
			tmp = delete_node(list, tmp);
		else
		{
			count--;
			tmp = tmp->next;
		}
	}
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;
	char	*st1;
	char	*st2;

	i = 0;
	st1 = (char *)s1;
	st2 = (char *)s2;
	while (st1[i] && st2[i] && st1[i] == st2[i])
		i++;
	return ((unsigned char)(st1[i]) - (unsigned char)(st2[i]));
}

