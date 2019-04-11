#include "selek.h"

void ft_rebasic(t_stockap *pac, t_basiks *tools)
{
	int				i;
	int				newnbline;
	struct	winsize	w;

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

void	ft_exit(int opt, char *msg, t_stock *stock)
{
	ft_termoder(2);
	if (opt != 2)
	{
		ft_freestock(stock);
		if (opt == 0)
			exit(0);
		ft_printfd(0, "%s\n", msg);
	}
	exit(1);
}
