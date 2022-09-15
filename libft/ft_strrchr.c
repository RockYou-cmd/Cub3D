/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:40:19 by ael-korc          #+#    #+#             */
/*   Updated: 2021/12/05 23:28:57 by ael-korc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	srch;
	int	fnd;

	fnd = 0;
	i = 0;
	srch = i;
	while (s[i])
	{
		if (s[i] == (char)c)
		{
			fnd = 1;
			srch = i;
		}
		i++;
	}
	if (c == '\0')
		return ((char *)(s + i));
	if (fnd)
		return ((char *)(s + srch));
	return (0);
}
