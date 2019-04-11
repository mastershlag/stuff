#include "selek.h"

int init_term()
{
    int ret;
    char *term_type = getenv("TERM");

    if (term_type == NULL)
    {
        ft_printfd(2, "TERM must be set (see 'env').\n");
        return -1;
    }
    ret = tgetent(NULL, term_type);
    if (ret == -1)
    {
        ft_printfd(2, "Could not access to the termcap database..\n");
        return -1;
    }
    else if (ret == 0)
    {
        ft_printfd(2, "'%s' is not defined in termcap database.\n", term_type);
        return -1;
    }
    return 0;
}

void 	ft_inicap(t_stockap *pac)
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

int ft_newread(t_keymaster *lock, t_stockap *pac,
	t_stock *stock, t_basiks *tools)
{
	while (1)
	{
		read(0, lock->buf, 255);
		lock->index = ft_getkey(lock->buf);
		if (ft_activkey(lock, pac, stock, tools))
			return (0);
		if (lock->index != 3)
			ft_memset(lock->buf, 0, 255);
		else
			break ;
	}
	return (0);
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

void	ft_inimain()
{
    if (signal(SIGINT, ft_controlcer) == SIG_ERR)
    	ft_exit(2, "", &g_stock);
    if (signal(SIGWINCH, ft_controlcer) == SIG_ERR)
    	ft_exit(2, "", &g_stock);
    if (signal(SIGCONT, ft_controlcer) == SIG_ERR)
    	ft_exit(2, "", &g_stock);
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
	if (!(out = (char*)malloc(sizeof(char) * stock->argc)))
		return (1);
	out[0] = 0;
	i = -1;
	while (stock->output[++i])
		if (stock->valid[i] == 1)
		{
			ft_strcat(out, stock->output[i]);
			ft_strcat(out, " ");
		}
	out[stock->argc - 1] = 0;
	ft_printfd(1, "%s", out);
	free(out);
	ft_freestock(stock);
	return (0);
}

void	ft_createstock(t_stock *stock, int argc, char **argv)
{
    int 		nb;
    int			i;

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
}

int main(int argc, char **argv)
{
    t_keymaster lock;
    int 		i;
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
		if (ft_newread(&lock, &g_pac, &g_stock, &g_tools))
			return (1);
		ft_rebasic(&g_pac, &g_tools);
		ft_termoder(2);
		if (ft_createout(&g_stock))
			return (1);
    }
    return (ret);
}
