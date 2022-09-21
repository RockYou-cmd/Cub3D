/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 22:28:45 by ael-korc          #+#    #+#             */
/*   Updated: 2021/11/15 18:01:14 by ael-korc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
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
	return (res);
}
