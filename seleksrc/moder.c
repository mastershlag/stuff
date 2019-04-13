/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharatyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 12:17:51 by pharatyk          #+#    #+#             */
/*   Updated: 2019/04/12 12:17:52 by pharatyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "selek.h"

void		ft_endit(t_stock *stock, t_stockap *pac, t_basiks *tools)
{
	free(stock->output);
	ft_rebasic(pac, tools);
	ft_exit(3, "", stock);
}

void		ft_controlcer(int signo)
{
	if (signo == SIGINT)
	{
		ft_rebasic(&g_pac, &g_tools);
		ft_termoder(2);
		exit(1);
	}
	if (signo == SIGWINCH)
	{
		ft_rebasic(&g_pac, &g_tools);
		ft_basic(&g_stock, &g_pac, &g_tools);
	}
	if (signo == SIGCONT)
		ft_cannoner();
}

void		ft_termoder(int mode)
{
	static struct termios	orig_tios;

	if (mode == 1)
	{
		if (tcgetattr(STDIN_FILENO, &orig_tios) == -1)
			exit(1);
	}
	else if (mode == 2)
	{
		if (tcsetattr(STDIN_FILENO, TCSANOW, &orig_tios) == -1)
			exit(1);
	}
}

int			ft_cannoner(void)
{
	struct termios	terter;

	if (tcgetattr(STDIN_FILENO, &terter) == -1)
		exit(1);
	ft_termoder(1);
	terter.c_lflag &= ~(ICANON);
	terter.c_lflag &= ~(ECHO);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &terter) == -1)
	{
		ft_termoder(2);
		ft_putstr_fd("Call to tcsetattr() failed\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

void		ft_basicmainloop(t_stock *stock, t_stockap *pac, t_basiks *tools,
	t_ijer *lol)
{
	if ((lol->i + (lol->j * tools->nbligne)) == stock->select)
		ft_printfd(0, "%s", pac->us_cap);
	if (stock->valid[(lol->i + (lol->j * tools->nbligne))] == 1)
		ft_printfd(0, "%s", pac->rv_cap);
	if ((lol->i + (lol->j * tools->nbligne)) == stock->select
		&& stock->valid[(lol->i + (lol->j * tools->nbligne))] == 1)
		ft_printfd(0, "%s", pac->md_cap);
	ft_printfd(0, "%s", stock->output[lol->i + (lol->j * tools->nbligne)]);
	ft_printfd(0, "%s", pac->me_cap);
}
