/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharatyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 12:18:05 by pharatyk          #+#    #+#             */
/*   Updated: 2019/04/12 12:23:41 by pharatyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "selek.h"

void	ft_inicap(t_stockap *pac)
{
	pac->rv_cap = tgetstr("mr", NULL);
	pac->nbcol = tgetnum("co");
	pac->nbline = tgetnum("li");
	pac->cl_cap = tgetstr("cl", NULL);
	pac->us_cap = tgetstr("us", NULL);
	pac->me_cap = tgetstr("me", NULL);
	pac->mb_cap = tgetstr("mb", NULL);
	pac->md_cap = tgetstr("md", NULL);
	pac->cm_cap = tgetstr("cm", NULL);
	pac->left_cap = tgetstr("le", NULL);
	pac->right_cap = tgetstr("nd", NULL);
	pac->ec_cap = tgetstr("ec", NULL);
	pac->ti_cap = tgetstr("ti", NULL);
	pac->up_cap = tgetstr("up", NULL);
	pac->down_cap = tgetstr("do", NULL);
	pac->dl_cap = tgetstr("dl", NULL);
	pac->savecurs_cap = tgetstr("sc", NULL);
	pac->backurs_cap = tgetstr("rc", NULL);
}

void	ft_freestock(t_stock *stock)
{
	int i;

	i = -1;
	while (stock->output[++i])
		free(stock->output[i]);
	free(stock->output[i]);
	free(stock->output);
}

void	ft_inimain(void)
{
	if (signal(SIGINT, ft_controlcer) == SIG_ERR)
		ft_exit(2, "", &g_stock);
	if (signal(SIGWINCH, ft_controlcer) == SIG_ERR)
		ft_exit(2, "", &g_stock);
	if (signal(SIGCONT, ft_controlcer) == SIG_ERR)
		ft_exit(2, "", &g_stock);
}

int		init_term(void)
{
	int		ret;
	char	*term_type;

	term_type = getenv("TERM");
	if (term_type == NULL)
	{
		ft_printfd(2, "TERM must be set (see 'env').\n");
		return (-1);
	}
	ret = tgetent(NULL, term_type);
	if (ret == -1)
	{
		ft_printfd(2, "Could not access to the termcap database..\n");
		return (-1);
	}
	else if (ret == 0)
	{
		ft_printfd(2, "'%s' is not defined in termcap database.\n", term_type);
		return (-1);
	}
	return (0);
}
