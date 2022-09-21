
#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	res = (char *)malloc(1 + ft_strlen(s1) + ft_strlen(s2));
	if (!res)
		return (NULL);
	while (s1[i] != 0)
	{
		res[j++] = s1[i++];
	}
	i = 0;
	while (s2[i] != 0)
	{
		res[j++] = s2[i++];
	}
	res[j] = 0;
	free(s1);
	free(s2);
	return (res);
}
