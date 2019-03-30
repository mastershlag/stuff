/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharatyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 10:43:08 by pharatyk          #+#    #+#             */
/*   Updated: 2018/11/13 10:43:10 by pharatyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmaster.h"

void	*ft_memalloc(size_t size)
{
	void	*out;

	if (!(out = malloc(size)))
		return (0);
	ft_bzero(out, size);
	return (out);
}
