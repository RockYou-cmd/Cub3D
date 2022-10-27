/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 22:09:07 by ael-korc          #+#    #+#             */
/*   Updated: 2021/12/05 17:45:54 by ael-korc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	**stock(const char *s, char **str, char c, int words)
{
	int	i;
	int	j;
	int	t;

	i = 0;
	j = 0;
	while (s[i] == c)
		i ++;
	while (j < words)
	{
		t = 0;
		while (s[i] != c && s[i] != 0)
		{
			str[j][t++] = s[i++];
		}
		while (s[i] == c)
			i ++;
		str[j][t] = 0;
		j ++;
	}
	return (str);
}

static	char	**alloc(const char *s, char **res, char c, int words)
{
	int	i;
	int	j;
	int	t;

	i = 0;
	j = 0;
	while (s[i] != 0 && j < words)
	{
		t = 0;
		while (s[i] == c)
			i ++;
		while (s[i] != c && s[i] != 0)
		{
			i ++;
			t ++;
		}
		res[j] = malloc((sizeof(char) * t) + 1);
		j ++;
	}
	return (res);
}

static	char	wordscount(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (s[i] == 0)
		return (0);
	while (s[i] == c)
		i ++;
	while (s[i] != 0)
	{
		if (s[i] == c && s[i - 1] != c)
			count ++;
		i ++;
	}
	if (s[i - 1] == c)
		return (count);
	else
		return (count + 1);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**res;

	if (!s)
		return (NULL);
	words = wordscount (s, c);
	res = malloc(sizeof(char *) * (words + 1));
	if (!res)
		return (NULL);
	res = alloc (s, res, c, words);
	res = stock (s, res, c, words);
	res[words] = (void *)0;
	return (res);
}
