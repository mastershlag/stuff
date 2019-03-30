#include "selek.h"

int		ft_addcara(t_keymaster *lock, t_stockap *pac)
{
	char *tmp;

	if (!(tmp = (char*)malloc(sizeof(char) * (lock->lenout + 1))))
		return (1);
	ft_strcpy(tmp, lock->out);
	free(lock->out);
	if (!(lock->out = (char*)malloc(sizeof(char) * (ft_strlen(tmp) + 2))))
		return (1);
	ft_strncpy(lock->out, tmp, (lock->curspos - lock->promptsize));
	lock->out[(lock->curspos - lock->promptsize)] = 0;
	ft_strcat(lock->out, lock->buf);
	ft_strcat(lock->out, tmp + (lock->curspos - lock->promptsize));
	lock->lenout += 1;
	free(tmp);
	return (0);
}

void	ft_addcaracursor(t_keymaster *lock, t_stockap *pac)
{
	int i;
	int savepos;

	lock->lvl = (int)((lock->lenout + lock->promptsize) / pac->nbcol);
	ft_printf("%s", pac->savecurs_cap);
	i = lock->curspos;
	savepos = i;
	while (++i < (lock->lenout + 1 + lock->promptsize))
		ft_simplegoright(lock, pac);
	i = -1;
	while (++i < lock->lvl)
		ft_printf("%s%s", pac->dl_cap, pac->up_cap);
	ft_printf("%s", pac->dl_cap);
	i = -1;
	while (++i < pac->nbcol)
		ft_printf("%s", pac->left_cap);
	ft_printf("%s%s%s", lock->prompt, lock->out, pac->backurs_cap);
	lock->curspos = savepos;
	ft_goright(lock, pac);
}

int		ft_delcara(t_keymaster *lock, t_stockap *pac)
{
	char *tmp;

	if (lock->curspos <= lock->promptsize)
		return (0);
	if (!(tmp = (char*)malloc(sizeof(char) * (lock->lenout + 1))))
		return (1);
	ft_strcpy(tmp, lock->out);
	free(lock->out);
	if (!(lock->out = (char*)malloc(sizeof(char) * ft_strlen(tmp))))
		return (1);
	ft_strncpy(lock->out, tmp, (lock->curspos - lock->promptsize - 1));
	lock->out[(lock->curspos - lock->promptsize - 1)] = 0;
	if (tmp[(lock->curspos - lock->promptsize - 1)])
		ft_strcator(lock->out, tmp + (lock->curspos - lock->promptsize));
	lock->lenout -= 1;
	free(tmp);
	return (-1);
}

void	ft_delcaracursor(t_keymaster *lock, t_stockap *pac)
{
	int i;
	int savepos;

	lock->lvl = (int)((lock->lenout + 1 + lock->promptsize) / pac->nbcol);
	ft_printf("%s", pac->savecurs_cap);
	i = lock->curspos;
	savepos = i;
	while (++i < (lock->lenout + 2 + lock->promptsize))
		ft_simplegoright(lock, pac);
	i = -1;
	while (++i < lock->lvl)
		ft_printf("%s%s", pac->dl_cap, pac->up_cap);
	ft_printf("%s", pac->dl_cap);
	i = -1;
	while (++i < pac->nbcol)
		ft_printf("%s", pac->left_cap);
	ft_printf("%s%s%s", lock->prompt, lock->out, pac->backurs_cap);
	lock->curspos = savepos;
	ft_goleft(lock, pac);
}

int		ft_activkey(t_keymaster *lock, t_stockap *pac)
{
	int hmm;

	// pac->nbcol = tgetnum("co");
	if (lock->index == 1) //gauche
		ft_goleft(lock, pac);
	if (lock->index == 2) //droite
		ft_goright(lock, pac);
	// if (lock->index == 5) //up
	// 	ft_printf("%s", pac->up_cap);
	// if (lock->index == 6) //down
	// 	ft_printf("%s", pac->down_cap);
	if (lock->index == 4) //del
	{
		hmm = ft_delcara(lock, pac);
		if (hmm != -1)
			return (hmm);
		ft_delcaracursor(lock, pac);
	}
	if (lock->index == 0)
	{
		if (ft_addcara(lock, pac))
			return (1);
		ft_addcaracursor(lock, pac);
	}
	// ft_printf("%s", pac->dl_cap);
	// i = -1;
	// while (++i < pac->nbcol)
	// 	ft_printf("%s", pac->left_cap);
	// ft_printf("{%3d:%3d} : %s", lock->curspos, ft_strlen(lock->out), lock->out);
	return (0);
}
