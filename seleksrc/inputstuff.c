/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputstuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharatyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 12:17:43 by pharatyk          #+#    #+#             */
/*   Updated: 2019/04/12 12:17:46 by pharatyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "selek.h"

int		ft_getkey(char *buf)
{
	if (buf[0] == 27 && buf[1] == '[' && buf[2] == 'D' && buf[3] == 0)
		return (1);
	if (buf[0] == 27 && buf[1] == '[' && buf[2] == 'C' && buf[3] == 0)
		return (2);
	if (buf[0] == 27 && buf[1] == '[' && buf[2] == 'A' && buf[3] == 0)
		return (5);
	if (buf[0] == 27 && buf[1] == '[' && buf[2] == 'B' && buf[3] == 0)
		return (6);
	if (buf[0] == 27 && buf[1] == 0)
		return (7);
	if (buf[0] == '\n')
		return (3);
	if (buf[0] == 127)
		return (4);
	if (buf[0] == 27 && buf[1] == 91 && buf[2] == 51 && buf[3] == 126
		&& buf[4] == 0)
		return (4);
	if (buf[0] == ' ')
		return (5);
	return (0);
}

void	ft_goleft(t_keymaster *lock, t_stockap *pac)
{
	int i;

	if (lock->curspos <= lock->promptsize)
		return ;
	if ((lock->curspos % pac->nbcol) == 0)
	{
		ft_printfd(0, "%s", pac->up_cap);
		i = -1;
		while (++i < pac->nbcol)
			ft_printfd(0, "%s", pac->right_cap);
	}
	else
		ft_printfd(0, "%s", pac->left_cap);
	lock->curspos -= 1;
}

void	ft_simplegoright(t_keymaster *lock, t_stockap *pac)
{
	if ((lock->curspos % pac->nbcol) == (pac->nbcol - 1))
		ft_printfd(0, "%s", pac->down_cap);
	else
		ft_printfd(0, "%s", pac->right_cap);
	lock->curspos += 1;
}

void	ft_goright(t_keymaster *lock, t_stockap *pac)
{
	if (lock->curspos >= (lock->lenout + lock->promptsize))
		return ;
	if ((lock->curspos % pac->nbcol) == (pac->nbcol - 1))
		ft_printfd(0, "%s", pac->down_cap);
	else
		ft_printfd(0, "%s", pac->right_cap);
	lock->curspos += 1;
}

void	ft_putatend(t_keymaster *lock, t_stockap *pac)
{
	int i;

	i = lock->curspos;
	while (++i < (lock->lenout + 1 + lock->promptsize))
		ft_goright(lock, pac);
}
