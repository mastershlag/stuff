/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selekmain.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharatyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 12:18:05 by pharatyk          #+#    #+#             */
/*   Updated: 2019/04/12 12:29:05 by pharatyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "selek.h"

void	ft_newread(t_keymaster *lock, t_stockap *pac,
		t_stock *stock, t_basiks *tools)
{
	ft_memset(lock->buf, 0, 255);
	while (1)
	{
		read(0, lock->buf, 255);
		lock->index = ft_getkey(lock->buf);
		ft_activkey(lock, pac, stock, tools);
		if (lock->index != 3)
			ft_memset(lock->buf, 0, 255);
		else
			break ;
	}
}

int		ft_createout(t_stock *stock)
{
	int			i;
	char		*out;

	i = -1;
	stock->argc = 0;
	while (stock->output[++i])
	{
		if (stock->valid[i] == 1)
			stock->argc += (ft_strlen(stock->output[i]) + 1);
	}
	if (!(out = (char*)malloc(sizeof(char) * (stock->argc + 1))))
		return (1);
	out[0] = 0;
	if (stock->argc)
		ft_fillout(stock, &out);
	ft_printfd(1, "%s", out);
	free(out);
	ft_freestock(stock);
	return (0);
}

void	ft_createstock(t_stock *stock, int argc, char **argv)
{
	int		nb;
	int		i;

	if (ft_cannoner())
		exit(1);
	if (!(stock->valid = (int*)malloc(sizeof(int) * (argc - 1))))
		ft_exit(2, "", stock);
	i = -1;
	while (++i < (argc - 1))
		stock->valid[i] = -1;
	if (!(stock->output = (char**)malloc(sizeof(char*) * argc)))
		ft_exit(2, "", stock);
	i = 0;
	nb = 0;
	while (argv[++i])
	{
		if (!(stock->output[nb] = (char*)malloc(sizeof(char)
						* (ft_strlen(argv[i]) + 1))))
			ft_exit(2, "", stock);
		ft_strcpy(stock->output[nb], argv[i]);
		nb++;
	}
	stock->output[nb] = 0;
	stock->select = 0;
	ft_stopstock(stock);
}

int		main(int argc, char **argv)
{
	t_keymaster lock;
	int			ret;

	ft_inimain();
	ret = init_term();
	ft_inicap(&g_pac);
	g_stock.argc = argc - 1;
	if (argc < 2)
	{
		ft_printfd(2, "usage: ft_select arg1 [arg2 ...]\n");
		return (0);
	}
	if (ret == 0)
	{
		ft_createstock(&g_stock, argc, argv);
		ft_basic(&g_stock, &g_pac, &g_tools);
		ft_newread(&lock, &g_pac, &g_stock, &g_tools);
		ft_rebasic(&g_pac, &g_tools);
		ft_termoder(2);
		if (ft_createout(&g_stock))
			return (1);
	}
	return (ret);
}
