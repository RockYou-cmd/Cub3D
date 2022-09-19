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

void remove_empty_lines(t_list_map **list)
{
	t_list_map *tmp;
	int count = 7;

	tmp = *list;	
	while (tmp && count)
	{
		if(tmp->line[0] == '\n')
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

char	*fill_wall(int (*arr)[6], int n, char *str)
{
	(*arr)[n] = 1;
	return (ft_strdup(str));
}

void fill_color(int (*arr)[6], int n, int (*colors)[3], char *str)
{
	char **colors_str;
	int count;

	colors_str = ft_split(str, ',');
	if (colors_str == NULL)
		end_game("colors problem");
	count = 0;
	while (colors_str[count] != NULL)
		count++;
	if (count != 3)
		end_game("colors problem");
	(*arr)[n] = 1;
	(*colors)[0] = ft_atoi(colors_str[0]);
	(*colors)[1] = ft_atoi(colors_str[1]);
	(*colors)[2] = ft_atoi(colors_str[2]);
	count = 0;
	while (count < 3)
	{
		if ((*colors)[count] > 255 || (*colors)[count] < 0)
			end_game("colors out of range");
		count++;
	}
}

t_props pars_props(t_list_map *list)
{
	int arr[6];
	t_props props;
	char **prop;
	int count = 6;
	int i = 0;

	while (count && list)
	{
		prop = ft_split(list->line, ' ');
		if (!prop || !prop[0] || !prop[1])
			end_game("map is wrong");
		if (ft_strcmp(prop[0], "NO") == 0)
			props.no = fill_wall(&arr, NO, prop[1]);
		else if (ft_strcmp(prop[0], "SO") == 0)
			props.so = fill_wall(&arr, SO, prop[1]);
		else if (ft_strcmp(prop[0], "WE") == 0)
			props.we = fill_wall(&arr, WE, prop[1]);
		else if (ft_strcmp(prop[0], "EA") == 0)
			props.ea = fill_wall(&arr, EA, prop[1]);
		else if (ft_strcmp(prop[0], "F") == 0)
			fill_color(&arr, F, &props.f, prop[1]);
		else if (ft_strcmp(prop[0], "C") == 0)
			fill_color(&arr, C, &props.c, prop[1]);
		list = list->next;
		count--;
	}
	while (!count && arr[i] == 1)
		i++;
	if (i != 6)
		end_game("map");
	return (props);
}

void	print_props(t_props props)
{
	printf("NO :: %s", props.no);
	printf("SO :: %s", props.so);
	printf("WE :: %s", props.we);
	printf("EA :: %s", props.ea);
	printf("F::: R: %d, G: %d, B: %d\n", props.f[0], props.f[1], props.f[2]);
	printf("C::: R: %d, G: %d, B: %d\n", props.c[0], props.c[1], props.c[2]);
}

int main()
{
	t_list_map *list;
	t_props props;
	list = creat_list_map("maps/insane.cub");
	remove_empty_lines(&list);
	props = pars_props(list);
	// print_props(props);
	print_list_map(&list);
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