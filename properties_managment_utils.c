/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   properties_managment_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-yamo <ael-yamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 01:18:42 by ael-yamo          #+#    #+#             */
/*   Updated: 2022/10/28 01:19:17 by ael-yamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_extention(char *file, char *extention)
{
	int	file_len;
	int	extention_len;

	file_len = ft_strlen(file);
	extention_len = ft_strlen(extention);
	if (file_len <= extention_len)
		end_game("extention problem");
	if (ft_strcmp(file + (file_len - extention_len), extention))
		end_game("extention problem");
}

char	*fill_wall(int (*arr)[6], int n, char *str)
{
	char	*wall;

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
	int				j;

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

char	**get_clr_str(char **str)
{
	char	**colors_str;
	int		i;
	char	*line;

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
