#include "selek.h"

int init_term()
{
    int ret;
    char *term_type = getenv("TERM");

    if (term_type == NULL)
    {
        fprintf(stderr, "TERM must be set (see 'env').\n");
        return -1;
    }

    ret = tgetent(NULL, term_type);

    if (ret == -1)
    {
        fprintf(stderr, "Could not access to the termcap database..\n");
        return -1;
    }
    else if (ret == 0)
    {
        fprintf(stderr, "Terminal type '%s' is not defined in termcap database (or have too few informations).\n", term_type);
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

int ft_newread(t_keymaster *lock, t_stockap *pac, t_stock *stock, t_basiks *tools)
{
	while (1)
	{
		read(1, lock->buf, 255);
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
}

int main(int argc, char **argv)
{
    t_stockap	pac;
    t_tcapter	cap;
    t_keymaster lock;
    t_basiks	tools;
    int 		i;
    int 		nb;
	t_stock		stock;
	char		*out;

    int ret = init_term();
    stock.argc = argc - 1;
    if (argc < 2)
    {
    	ft_printf("usage: ft_select arg1 [arg2 ...]\n");
    	return (0);
    }
    if (signal(SIGINT, ft_controlcer) == SIG_ERR)
    	ft_printf("sigint escaped the program");
    ft_inicap(&pac);
    if (ret == 0)
    {
		// ft_printf("cl_cap : %s", pac.cl_cap);
		// tputs (cl_cap, 1, putchar);
  //   	ft_printf("jusqu'ici tt va bien\n");
  //       ft_printf("col:%4d, lign:%4d\n", pac.nbcol, pac.nbline);
  //       if (tgetflag("os") != 0)
		// 	ft_printf("os\n");
		// else
		// 	ft_printf("noos\n");
		// ft_printf("%sPTN%s\n", pac.us_cap, pac.me_cap);
		// ft_printf("%scligno%s\n", pac.mb_cap, pac.me_cap);
		// ft_printf("%sbold%s\n", pac.md_cap, pac.me_cap);
		// ft_printf("%s%s%sall_3%s\n", pac.md_cap, pac.us_cap, pac.mb_cap, pac.me_cap);
		// tputs(tgoto(cm_cap, 15, 18), 1, putchar);
		// ft_printf("%s", ti_cap);

		if (ft_cannoner(&cap))
			return (1);
		if (!(stock.valid = (int*)malloc(sizeof(int) * (argc - 1))))
			return (1);
		i = -1;
		while (++i < (argc - 1))
			stock.valid[i] = -1;
		if (!(stock.output = (char**)malloc(sizeof(char*) * argc)))
			return (1);
		i = 0;
		nb = 0;
		while (argv[++i])
		{
			if (!(stock.output[nb] = (char*)malloc(sizeof(char) * (ft_strlen(argv[i]) + 1))))
				return (1);
			ft_strcpy(stock.output[nb], argv[i]);
			nb++;
		}
		stock.output[nb] = 0;
		stock.select = 0;
		ft_basic(&stock, &pac, &tools);
		if (ft_newread(&lock, &pac, &stock, &tools))
			return (1);
		ft_rebasic(&pac, &tools);
		// ft_printf("\n{%s}:%d = %d\n", lock.out, ft_strlen(lock.out), lock.lenout);
		// free(lock.out);
		// free(lock.prompt);
		// write(1, "\n", 1);
		ft_termoder(2);
		// ft_printf("selectionés:\n");
		i = -1;
		stock.argc = 0;
		while (stock.output[++i])
		{
			if (stock.valid[i] == 1)
				stock.argc += (ft_strlen(stock.output[i]) + 1);
		}
		if (!(out = (char*)malloc(sizeof(char) * stock.argc)))
			return (1);
		out[0] = 0;
		i = -1;
		while (stock.output[++i])
			if (stock.valid[i] == 1)
			{
				ft_strcat(out, stock.output[i]);
				ft_strcat(out, " ");
			}
		out[stock.argc - 1] = 0;
		ft_printf("%s", out);
		free(out);
		ft_freestock(&stock);
    }
    return (ret);
}
