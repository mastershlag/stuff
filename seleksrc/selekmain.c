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

int ft_newread(t_keymaster *lock, t_stockap *pac)
{
	if (!(lock->out = (char*)malloc(sizeof(char))))
		return (1);
	lock->out[0] = 0;
	lock->lenout = 0;
	ft_printf("%s", lock->prompt);
	lock->curspos = lock->promptsize;
	lock->lvl = 0;
	while (1)
	{
		read(1, lock->buf, 255);
		lock->index = ft_getkey(lock->buf);
		if (ft_activkey(lock, pac))
			return (1);
		if (lock->index != 3)
			ft_memset(lock->buf, 0, 255);
		else
			break ;
	}
	ft_putatend(lock, pac);
	return (0);
}

int main(int argc, char **argv)
{
    t_stockap	pac;
    t_tcapter	cap;
    t_keymaster lock;
    int 		i;

    int ret = init_term();
    (void)argc;
    (void)argv;

    if (signal(SIGINT, ft_controlcer) == SIG_ERR)
    	ft_printf("sigint escaped the program");
    ft_inicap(&pac);
    if (ret == 0)
    {
    	// ft_printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		ft_printf("cl_cap : %s", pac.cl_cap);
		// tputs (cl_cap, 1, putchar);
    	ft_printf("jusqu'ici tt va bien\n");
        ft_printf("col:%4d, lign:%4d\n", pac.nbcol, pac.nbline);
        if (tgetflag("os") != 0)
			ft_printf("os\n");
		else
			ft_printf("noos\n");
		ft_printf("%sPTN%s\n", pac.us_cap, pac.me_cap);
		ft_printf("%scligno%s\n", pac.mb_cap, pac.me_cap);
		ft_printf("%sbold%s\n", pac.md_cap, pac.me_cap);
		ft_printf("%s%s%sall_3%s\n", pac.md_cap, pac.us_cap, pac.mb_cap, pac.me_cap);
		// tputs(tgoto(cm_cap, 15, 18), 1, putchar);
		// ft_printf("%s", ti_cap);
		if (ft_cannoner(&cap))
			return (1);
		if (!(lock.prompt = (char*)malloc(sizeof(char) * 24)))
			return (1);
		ft_strcpy(lock.prompt, "\e[96mMastershell\e[0m$> ");
		lock.promptsize = 14;
		// if (!(lock.prompt = (char*)malloc(sizeof(char) * 4)))
		// 	return (1);
		// ft_strcpy(lock.prompt, "go>");
		// lock.promptsize = 3;
		if (ft_newread(&lock, &pac))
			return (1);
		// write(1, "|end|", 5);
		ft_printf("\n{%s}:%d = %d\n", lock.out, ft_strlen(lock.out), lock.lenout);
		free(lock.out);
		free(lock.prompt);
		write(1, "\n", 1);
		ft_termoder(2);
		// ft_printf("%s", pac.me_cap);
    }
    return (ret);
}
