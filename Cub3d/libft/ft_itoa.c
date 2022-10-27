/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 20:08:57 by ael-korc          #+#    #+#             */
/*   Updated: 2022/03/12 18:53:29 by ael-korc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	lennbr(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static int	stock(long long int a, long int n)
{
	long int	t;
	int			j;
	int			len;

	len = lennbr(n);
	t = 0;
	j = 0;
	while (j < len)
	{
		t = n;
		t /= a;
		a /= 10;
		t %= 10;
		return (t);
	}
	return (0);
}

static long long int	power(int i, int n)
{
	int				c;
	long long int	p;

	p = 1;
	c = 0;
	if (n < 0)
		i -= 1;
	while (c < i)
	{
		p *= 10;
		c ++;
	}
	return (p);
}

char	*ft_itoa(int n)
{
	char			*ptr;
	int				j;
	long long int	a;
	int				len;
	long int		t;

	t = n;
	j = 0;
	len = lennbr(t);
	a = power(lennbr(t), t);
	ptr = (char *)malloc(sizeof(char) * len + 1);
	if (!ptr)
		return (0);
	if (n < 0)
	{
		t = -t;
		ptr[j++] = '-';
	}
	while (j < len)
		ptr[j++] = stock((a /= 10), t) + '0';
	ptr[j] = '\0';
	return (ptr);
}
