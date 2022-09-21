/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:55:41 by ael-korc          #+#    #+#             */
/*   Updated: 2021/11/30 14:09:31 by ael-korc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_rsearch(const char *ss1, const char *sset)
{
	int	i;
	int	j;
	int	t;

	i = ft_strlen (ss1) - 1;
	while (ss1[i] != 0)
	{
		j = 0;
		t = 0;
		while (sset[j] != 0)
		{
			if (ss1[i] == sset[j])
				t = 1;
			j ++;
		}
		if (!t)
			return (i);
		i --;
	}
	return (i);
}

static int	ft_search(const char *ss1, const char *sset)
{
	int	i;
	int	j;
	int	t;

	i = 0;
	while (ss1[i] != 0)
	{
		j = 0;
		t = 0;
		while (sset[j] != 0)
		{
			if (ss1[i] == sset[j])
				t = 1;
			j ++;
		}
		if (!t)
			return (--i);
		i ++;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		s;
	int		e;
	char	*str;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup(s1));
	i = 0;
	s = ft_search (s1, set);
	e = ft_rsearch (s1, set);
	if (s >= e)
		return (ft_strdup(""));
	str = (char *)malloc(((e - s) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (s < e)
		str[i++] = s1[++s];
	str[i] = 0;
	return (str);
}
