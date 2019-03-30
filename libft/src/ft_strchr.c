/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharatyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 13:14:19 by pharatyk          #+#    #+#             */
/*   Updated: 2018/11/09 13:14:21 by pharatyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmaster.h"

char	*ft_strchr(const char *s, int c)
{
	if (c == 0)
		return ((char *)s + ft_strlen(s));
	while (*s)
	{
		if (*s == c)
			return ((char*)s);
		s++;
	}
	return (0);
}

char	*ft_strchrstr(const char *s, char *find)
{
	int i;
	int j;

	if (!find)
		return ((char *)s + ft_strlen(s));
	i = -1;
	while (s[++i])
	{
		if (s[i] == find[0])
		{
			j = 0;
			while (s[j + i] == find[j] && find[j] && s[j + i])
				j++;
			if (find[j] == 0)
				return ((char*)(s + i));
		}
	}
	return (0);
}
