#include "selek.h"

void ft_rebasic(t_stockap *pac, t_basiks *tools)
{
	int i;

	i = -1;
	while (++i < tools->nbligne)
		ft_printf("%s%s", pac->up_cap, pac->dl_cap);
}