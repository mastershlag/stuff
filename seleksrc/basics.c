/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basics.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharatyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 12:17:28 by pharatyk          #+#    #+#             */
/*   Updated: 2019/04/12 12:17:31 by pharatyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "selek.h"

static int	ft_maxer(t_stock *stock, int max)
{
	char	*tmp;
	int		i;
	int		j;

	i = -1;
	while (stock->output[++i])
	{
		if (!(tmp = (char*)malloc(sizeof(char) * (max + 2))))
			return (1);
		j = -1;
		while (stock->output[i][++j])
			tmp[j] = stock->output[i][j];
		tmp[j] = 0;
		j--;
		while (++j < max)
			tmp[j] = ' ';
		tmp[j] = 0;
		free(stock->output[i]);
		if (!(stock->output[i] = (char*)malloc(sizeof(char) * (max + 2))))
			return (1);
		stock->output[i] = ft_strcpy(stock->output[i], tmp);
		free(tmp);
	}
	return (0);
}

static int	ft_maxfinder(t_stock *stock, t_basiks *tools)
{
	struct winsize w;

	if ((ioctl(0, TIOCGWINSZ, &w)) == -1)
		return (1);
	tools->nbobj = 0;
	tools->max = 0;
	while (stock->output[tools->nbobj])
	{
		if ((int)ft_strlen(stock->output[tools->nbobj]) > tools->max)
			tools->max = ft_strlen(stock->output[tools->nbobj]);
		tools->nbobj += 1;
	}
	if ((tools->max % 8) == 0)
		tools->max += 1;
	while ((tools->max % 8) != 0)
		tools->max += 1;
	if (ft_maxer(stock, tools->max))
		return (1);
	tools->lignemax = 0;
	while ((tools->lignemax * tools->max) < w.ws_col)
		tools->lignemax += 1;
	if ((tools->lignemax * tools->max) > w.ws_col)
		tools->lignemax -= 1;
	return (0);
}

static int	ft_outcreator(t_basiks *tools)
{
	int		isimpair;
	float	truenbline;

	if (tools->lignemax == 0)
	{
		tools->nbligne = -1;
		return (0);
	}
	isimpair = (tools->nbobj % 2);
	truenbline = (float)tools->nbobj / (float)(tools->lignemax);
	if (truenbline > (int)truenbline)
		tools->nbligne = (int)truenbline + 1;
	else
		tools->nbligne = (int)truenbline;
	return (0);
}

static void	ft_reboot(t_stock *stock)
{
	int i;
	int j;

	i = -1;
	while (stock->output[++i])
	{
		j = ft_strlen(stock->output[i]);
		while (stock->output[i][--j] == ' ')
			stock->output[i][j] = 0;
	}
}

int			ft_basic(t_stock *stock, t_stockap *pac, t_basiks *tools)
{
	int		i;
	int		j;
	t_ijer	lol;

	if (ft_maxfinder(stock, tools) || ft_outcreator(tools))
		return (1);
	tools->lignemax = 0;
	if (tools->nbligne >= 0)
		while ((tools->lignemax * tools->nbligne) < tools->nbobj)
			tools->lignemax += 1;
	i = -1;
	while (++i < tools->nbligne)
	{
		j = -1;
		while (++j < tools->lignemax && stock->output[i + (j * tools->nbligne)]
			&& (i + (j * tools->nbligne)) < tools->nbobj)
		{
			lol.i = i;
			lol.j = j;
			ft_basicmainloop(stock, pac, tools, &lol);
		}
		ft_printfd(0, "\n");
	}
	ft_reboot(stock);
	return (0);
}
