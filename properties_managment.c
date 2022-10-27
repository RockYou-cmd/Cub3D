#include "cub3d.h"

void	check_extention(char *file, char *extention)
{
	int file_len;
	int extention_len;

	file_len = ft_strlen(file);
	extention_len = ft_strlen(extention);
	if (file_len <= extention_len)
		end_game("extention problem");
	if (ft_strcmp(file + (file_len - extention_len), extention))
		end_game("extention problem");
}

char	*fill_wall(int (*arr)[6], int n, char *str)
{
	char *wall;

	(*arr)[n] = 1;
	check_extention(str, ".xpm");
	wall = ft_strdup(str);
	if (!wall)
		end_game("problem with malloc");
	return (wall);
}

void	ft_striteri2(char **s, void (*f)(char))
{
	unsigned int	i;
	int j;

	if (s == NULL)
		end_game("colors problem");
	j = 0;
	if (s)
	{
		while (s[j])
		{
			i = 0;
			while (s[j][i])
			{
				(*f)(s[j][i]);
				i++;
			}
			j++;
		}
	}
}

void	check_digit(char c)
{
	if (!ft_isdigit(c))
		end_game("colors are not digits");
}

char **get_clr_str(char **str)
{
	char **colors_str;

	int i;
	char *line;

	i = 1;
	line = ft_strdup("");
	if (!line)
		end_game("malloc error");
	while (str[i])
	{
		line = ft_strjoin(line, str[i]);
		i++;
	}
	colors_str = ft_split(line, ',');
	free(line);
	if (!colors_str)
		end_game("malloc problem");
	return (colors_str);
}

void fill_color(int (*arr)[6], int n, int (*colors)[3], char **str)
{
	char **colors_str;
	int count;

	colors_str = get_clr_str(str);
	ft_striteri2(colors_str, check_digit);
	count = 0;
	while (colors_str[count] != NULL)
		count++;
	if (count != 3)
		end_game("colors problem");
	(*arr)[n] = 1;
	(*colors)[0] = ft_atoi(colors_str[0]);
	(*colors)[1] = ft_atoi(colors_str[1]);
	(*colors)[2] = ft_atoi(colors_str[2]);
	free_2d_arr(colors_str);
	count = 0;
	while (count < 3)
	{
		if ((*colors)[count] > 255 || (*colors)[count] < 0)
			end_game("colors out of range");
		count++;
	}
}

static int	count_prop(char **prop)
{
	int i;

	i = 0;
	if (!prop)
		return (0);
	while (prop[i])
	{
		i++;
	}
	return (i);
}

void	free_2d_arr(char **arr)
{
	int i;

	if (!arr)
		return;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void pars_props_utils(char **prop, int (*arr)[6])
{
	if (count_prop(prop) == 2 && ft_strcmp(prop[0], "NO") == 0)
		data.props.no = fill_wall(arr, NO, prop[1]);
	else if (count_prop(prop) == 2 && ft_strcmp(prop[0], "SO") == 0)
		data.props.so = fill_wall(arr, SO, prop[1]);
	else if (count_prop(prop) == 2 && ft_strcmp(prop[0], "WE") == 0)
		data.props.we = fill_wall(arr, WE, prop[1]);
	else if (count_prop(prop) == 2 && ft_strcmp(prop[0], "EA") == 0)
		data.props.ea = fill_wall(arr, EA, prop[1]);
	else if (count_prop(prop) >= 2 && ft_strcmp(prop[0], "F") == 0)
		fill_color(arr, F, &data.props.f_rgb, prop);
	else if (count_prop(prop) >= 2 && ft_strcmp(prop[0], "C") == 0)
		fill_color(arr, C, &data.props.c_rgb, prop);
}

void pars_props_utils2(int (*arr)[6], int count)
{
	int i = 0;

	while (!count && (*arr)[i] == 1)
		i++;
	if (i != 6)
		end_game("map");
}

void pars_props(t_list_map *list)
{
	int arr[6];
	char **prop;
	int count = 6;
	char *line;

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
	int count = 6;
	while (count)
	{
		delete_node(list, *list);
		count--;
	}
}

void	print_props(t_props props)
{
	printf("NO :: %s\n", props.no);
	printf("SO :: %s\n", props.so);
	printf("WE :: %s\n", props.we);
	printf("EA :: %s\n", props.ea);
	printf("F::: R: %d, G: %d, B: %d\n", data.props.f_rgb[0], data.props.f_rgb[1], data.props.f_rgb[2]);
	printf("C::: R: %d, G: %d, B: %d\n", data.props.c_rgb[0], data.props.c_rgb[1], data.props.c_rgb[2]);
	printf("PLD:: %d", props.player_l_d);
}