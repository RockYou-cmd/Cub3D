#include "cub3d.h"

int	checkmap()
{
	int	i;
	int	t;

	i = 0;
	t = 0;
	while(t < data.map.rows)
	{
		i = 0;
		while(data.map.array[t][i])
		{
			// if ((t == 0 || t == data.map.rows) && data.map.array[t][i] != '1' && data.map.array[t][i] != ' ' && data.map.array[t][i] != '\n')
			// 	return 0;
			// if (data.map.array[t][i] == '0' && (data.map.array[t][i - 1] == ' ' || data.map.array[t][i + 1] == ' ' || data.map.array[t][i + 1] == '\n'))
			// 	return 0;
			// if (data.map.array[t][i] == '0' && data.map.array[t + 1][i] && data.map.array[t + 1][i] != '0' && data.map.array[t + 1][i] != '1')
			// 	return 0;
			// if (data.map.array[t][i] == '0' && data.map.array[t - 1][i] && data.map.array[t - 1][i] != '0' && data.map.array[t - 1][i] != '1')
			// 	return 0;
			// if (data.map.array[t][i] == '0' && !data.map.array[t + 1][i])
			// 	return 0;
			// if (data.map.array[t][i] == '0' && !data.map.array[t - 1][i])
			// 	return 0;
			if (data.map.array[t][i] == 'E')
			{
				data.map.array[t][i] = '0';
				data.player.x = i * data.square_size + 15;
				data.player.y = t * data.square_size + 15;
			}
			i ++;
		}
		t ++;
	}
	return 1;
}

void	file_ext(char *file)
{
	char	*cub;

	cub = ft_strnstr(file, ".cub", ft_strlen(file));
	if (cub)
	{
		if (cub == file + ft_strlen(file) - 4)
			return ;
	}
	end_game("ERROR MAP EXTENSION");
}


int	fillmap(char *line)
{
	char			**new_map;
	unsigned long	i;

	i = 0;
	data.map.rows = data.map.rows + 1;
	new_map = ft_calloc(sizeof(char *), (data.map.rows + 1));
	while (data.map.array[i])
	{
		new_map[i] = data.map.array[i];
		i++;
	}
	new_map[i] = line;
	new_map[i + 1] = NULL;
	free(data.map.array);
	data.map.array = new_map;
	return (0);
}
void	read_map(char *file)
{
	int		fd;
	char	*line;

	file_ext(file);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		printf("Couldn't open map file.");
	line = get_next_line(fd);
	if (!line)
		printf("Failed to read map");
	data.map.cols = ft_strlen(line) - 1;
	data.map.rows = 0;
	data.map.array[0] = NULL;
	while (line)
	{
		fillmap(line);
		line = get_next_line(fd);
		if (line && ft_strlen(line) - 1 > (unsigned long)data.map.cols)
			data.map.cols = ft_strlen(line) - 1;
	}
	if (!checkmap())
		end_game("WRONG MAP SIZE.");
	close(fd);
}