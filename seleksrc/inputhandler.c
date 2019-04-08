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

void	ft_suppr(t_stock *stock)
{
	int i;

	stock->argc -= 1;
	free(stock->output[stock->select]);
	if (stock->argc == 0)
	{
		stock->output[0] = stock->output[1];
		return ;
	}
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

int		ft_activkey(t_keymaster *lock, t_stockap *pac, t_stock *stock, t_basiks	*tools)
{
	int hmm;

	if (lock->index == 1) //gauche
		ft_lefter(stock);
	if (lock->index == 2) //droite
		ft_righter(stock);
	if (lock->index == 5) //droite
		ft_validate(stock);
	if (lock->index == 4) //del
		ft_suppr(stock);

	if (stock->argc == 0)
		return (1);
	ft_rebasic(pac, tools);
	ft_basic(stock, pac, tools);
	return (0);
}
