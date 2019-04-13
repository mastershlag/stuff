/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputhandler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharatyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 12:17:37 by pharatyk          #+#    #+#             */
/*   Updated: 2019/04/12 12:17:38 by pharatyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "selek.h"

void	ft_righter(t_stock *stock)
{
	stock->select = (stock->select + 1) % stock->argc;
}

void	ft_lefter(t_stock *stock)
{
	int test;

	test = stock->select - 1;
	if (test == -1)
		stock->select = stock->argc - 1;
	else
		stock->select = test % stock->argc;
}

void	ft_validate(t_stock *stock)
{
	stock->valid[stock->select] *= -1;
	ft_righter(stock);
}

void	ft_suppr(t_stock *stock, t_stockap *pac, t_basiks *tools)
{
	int i;

	stock->argc -= 1;
	free(stock->output[stock->select]);
	if (stock->argc == 0)
		ft_endit(stock, pac, tools);
	if (stock->argc == stock->select)
	{
		stock->output[stock->select] = stock->output[stock->select + 1];
		stock->select = 0;
		return ;
	}
	i = stock->select - 1;
	while (++i < (stock->argc))
	{
		stock->output[i] = stock->output[i + 1];
		stock->valid[i] = stock->valid[i + 1];
	}
	stock->output[i] = stock->output[i + 1];
	return ;
}

void	ft_activkey(t_keymaster *lock, t_stockap *pac,
	t_stock *stock, t_basiks *tools)
{
	if (lock->index == 1)
		ft_lefter(stock);
	if (lock->index == 2)
		ft_righter(stock);
	if (lock->index == 5)
		ft_validate(stock);
	if (lock->index == 4)
		ft_suppr(stock, pac, tools);
	if (lock->index == 7)
	{
		ft_rebasic(pac, tools);
		ft_exit(0, "", stock);
	}
	ft_rebasic(pac, tools);
	ft_basic(stock, pac, tools);
}
