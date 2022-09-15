#include "cub3d.h"

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
	int i;
	int t;

	i = 0;
	t = 0;
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
	}
	while(data.map.array[t][i])
	{
		i = 0;
		while(data.map.array[t][i])
		{
			if (data.map.array[t][i] == 'E')
				printf("player : %c\n", data.map.array[t][i]);
			i ++;
		}
		t ++;
	}
	close(fd);
}