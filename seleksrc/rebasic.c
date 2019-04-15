/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rebasic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharatyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 12:17:57 by pharatyk          #+#    #+#             */
/*   Updated: 2019/04/12 12:17:59 by pharatyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "selek.h"

void		ft_rebasic(t_stockap *pac, t_basiks *tools)
{
	int				i;
	int				newnbline;
	struct winsize	w;

	if ((ioctl(0, TIOCGWINSZ, &w)) == -1)
		return ;
	newnbline = 0;
	while ((newnbline * tools->max) < w.ws_col)
		newnbline += 1;
	if ((newnbline * tools->max) > w.ws_col)
		newnbline -= 1;
	if (newnbline < tools->lignemax)
		tools->nbligne += tools->nbligne;
	i = -1;
	while (++i < tools->nbligne)
		ft_printfd(0, "%s%s", pac->up_cap, pac->dl_cap);
}

void		ft_exit(int opt, char *msg, t_stock *stock)
{
	ft_termoder(2);
	if (opt < 2)
	{
		ft_freestock(stock);
		if (opt == 0)
			exit(0);
		ft_printfd(0, "%s\n", msg);
	}
	if (opt == 3)
		exit(0);
	exit(1);
}

static void	ft_stopstocker(t_stock *stock, int i)
{
	int		j;
	char	*tmp;

	if (!(tmp = (char*)malloc(sizeof(char)
		* (ft_strlen(stock->output[i]) + 2))))
		ft_exit(2, "", stock);
	j = -1;
	while (stock->output[i][++j] != '\n')
		tmp[j] = stock->output[i][j];
	tmp[j] = '\\';
	tmp[++j] = 'n';
	tmp[j + 1] = 0;
	ft_strcat(tmp, stock->output[i] + j);
	free(stock->output[i]);
	if (!(stock->output[i] = (char*)malloc(sizeof(char)
		* (ft_strlen(tmp) + 1))))
		ft_exit(2, "", stock);
	ft_strcpy(stock->output[i], tmp);
	free(tmp);
}

void		ft_stopstock(t_stock *stock)
{
	int		i;

	i = -1;
	while (stock->output[++i])
		if (ft_strrchr(stock->output[i], '\n'))
		{
			ft_stopstocker(stock, i);
			i--;
		}
}
