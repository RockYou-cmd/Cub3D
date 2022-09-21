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


int count_list_elms(t_list_map *list)
{
	int count;
	int new_line;

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

typedef struct s_line
{
	char *line;
	int len;
} t_line;

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

t_line *list_to_arr(t_list_map *list)
{
	t_line *lines;
	int line_numbers;
	int i;

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
		lines[i].len = ft_strlen(lines[i].line);
		if (!lines[i].line)
			end_game("strdup err");
		list = list->next;
		i++;
	}
	lines[i].line = NULL;
	return lines;
}

void check_outside(int start, int end, t_line *lines, int index)
{
	while (start < end)
	{
		if (lines[index].line[start] == '0')
			end_game("map not closed 1");
		if (lines[index].line[start] == ' ' && 
		(lines[index + 1].len >= lines[index].len && 
		lines[index + 1].line[start] == '0'))
			end_game("map not closed 2");
		start++;
	}
}
int is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int check_space(t_line *lines, int index, int i)
{
	if (i != 0 && lines[index].line[i - 1] == '0')
		return (0);
	if (i != (lines[index].len - 1) && 
	(lines[index].line[i + 1] == '0' || is_player(lines[index].line[i + 1])))
		return (0);
	if (index != 0 && lines[index - 1].len >= lines[index].len && 
	lines[index - 1].line[i] == '0')
		return (0);
	if (lines[index].line && lines[index + 1].len >= lines[index].len && 
	lines[index + 1].line[i] == '0')
		return (0);
	return (1);
}

void check_line(t_line *lines, int index)
{
	int i;

	i = 0;
	while (lines[index].line && lines[index].line[i] && lines[index].line[i] == ' ')
	{
		if (lines[index + 1].line[i] == '0')
			end_game("map is not closed 3");
		i++;
	}
	if(!lines[index].line[i])
		return;
	if (lines[index].line[i] != '1' || (lines[index].line[lines[index].len - 1] != '1' 
	&& lines[index].line[lines[index].len - 1] != ' '))
			end_game("map is not closed 4");
	if (index != 0 && (lines[index - 1].len < lines[index].len))
		check_outside(lines[index - 1].len, lines[index].len, lines,index);
	if (index != 0 && (lines[index - 1].len == lines[index].len))
	{
		if (lines[index - 1].line[lines[index].len - 1] != '1')
			end_game("map is not closed 5");
	}
	else
		check_outside(lines[index].len, lines[index - 1].len, lines, index - 1);
}

int all_spaces(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

void check_first_line(t_line *lines)
{
	int i;
	int j;

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

void check_last_line(t_line *lines, int i)
{
	int j;

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

void map_is_closed(t_line *lines)
{
	int index;
	int i;

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

int check_player(char c)
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

void check_map_elm(t_line *lines, t_props *props)
{
	int index;
	int i;
	int player;

	index = 1;
	player = -1;
	while (lines[index].line)
	{
		i = 0;
		while (lines[index].line[i] != '\0')
		{
			if (check_player(lines[index].line[i]) != -1 && player == -1)
			{
				player = 1;
				(*props).player_l_d = check_player(lines[index].line[i]);
			}
			else if (check_player(lines[index].line[i]) != -1 && player != -1)
				end_game("too many players");
			if (lines[index].line[i] == ' ' && !check_space(lines, index, i))
				end_game("map is wrong");
			i++;
		}
		index++;
	}
	if (player == -1)
		end_game("no player found");
}

void print_arr(char **lines)
{
	int i;

	i = 0;
	while (lines[i])
	{
		printf("%s\n", lines[i]);
		i++;
	}
	
}

void width_height(t_line *lines, t_map *map)
{
	int i;

	if (!lines || !map)
		return ;
	i = 0;
	while (lines[i].line)
	{
		if (map->cols < lines[i].len)
			map->cols = lines[i].len;
		i++;
	}
	map->rows = i;
}

t_map line_to_str(t_line *lines)
{
	t_map map;
	int i;
	int len;

	map.rows = -1;
	map.cols = -1;
	width_height(lines, &map);
	if (map.cols == -1 || map.rows == -1)
		end_game("map 69");
	map.array = malloc(sizeof(char *) * map.cols);
	if (!lines)
		end_game("map 69");
	i = 0;
	len = 0;
	while (lines[i].line)
	{
		map.array[i] = lines[i].line;
		i++;
	}
	map.array[i] = lines[i].line;
	free(lines);
	lines = NULL;
	return (map);
}

void	free_list(t_list_map **list)
{
	t_list_map *tmp;

	tmp = *list;
	while (tmp)
		tmp = delete_node(list, tmp);
}

int main()
{
	t_list_map *list;
	t_props props;
	t_line *lines;
	t_map map;

	list = creat_list_map("maps/map2.cub");
	remove_empty_lines(&list);
	props = pars_props(list);
	props.player_l_d = -1;
	delete_props(&list);
	lines = list_to_arr(list);
	free_list(&list);
	map_is_closed(lines);
	check_map_elm(lines, &props);
	map = line_to_str(lines);
	free_list(&list);
	// print_arr(map.array);
	// print_props(props);
	// check_all_spaces(lines);
	end_game(NULL);
	// print_list_map(&list);
	return (0);
}

// void	check_prop()
// {
	
// }

// void parsing(char *file)
// {
// 	//later check extention
// 	check_prop();
// }