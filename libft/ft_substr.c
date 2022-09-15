/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 00:12:40 by ael-korc          #+#    #+#             */
/*   Updated: 2021/12/05 23:19:52 by ael-korc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*sub;

	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	sub = (char *)malloc(len * sizeof(char));
	if (!sub)
		return (NULL);
	i = 0;
	j = 0;
	while (i <= start - 1 && start != 0)
		i ++;
	while (j < len && s[i] != 0)
	{
		sub[j] = s[i];
		i ++;
		j ++;
	}
	sub[j] = 0;
	return (sub);
}
