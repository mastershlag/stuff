/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharatyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 13:16:11 by pharatyk          #+#    #+#             */
/*   Updated: 2018/11/09 13:16:13 by pharatyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmaster.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	char *cpdest;

	cpdest = dest;
	while (n > 0 && *src)
	{
		*cpdest++ = *src++;
		--n;
	}
	while (n > 0)
	{
		*cpdest++ = 0;
		--n;
	}
	return (dest);
}
