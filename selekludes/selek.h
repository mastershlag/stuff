
#ifndef SELEK_H
# define SELEK_H

# include "libmaster.h"
# include <curses.h>
# include <term.h>
# include <sys/ioctl.h>

typedef struct			s_tcapter
{
	struct termios	terter;
}						t_tcapter;

typedef struct			s_stockap
{
	int		nbline;
	int		nbcol;
	char	*ec_cap;
	char	*left_cap;
	char	*right_cap;
	char	*up_cap;
	char	*down_cap;
	char	*dl_cap;
	char	*savecurs_cap;
	char	*backurs_cap;
	char	*cl_cap;
	char	*us_cap;
	char	*me_cap;
	char	*mb_cap;
	char	*md_cap;
	char	*cm_cap;
	char	*ti_cap;
	char	*rv_cap;
}						t_stockap;

typedef struct			s_keymaster
{
	char	buf[256];
	char	*prompt;
	int		promptsize;
	char	*out;
	int		lenout;
	int		curspos;
	int		index;
	int		lvl;
}						t_keymaster;

typedef struct	s_stock
{
	char	**output;
	int		select;
	int		*valid;
	int		argc;
}				t_stock;

typedef struct	s_basiks
{
	int		max;
	int		nbobj;
	int		nbligne;
	int		lignemax;
}				t_basiks;

void		ft_termoder(int mode);
int			ft_cannoner(t_tcapter *cap);
void		ft_controlcer(int signo);
int			ft_getkey(char *buf);
void		ft_putatend(t_keymaster *lock, t_stockap *pac);
void		ft_goright(t_keymaster *lock, t_stockap *pac);
void		ft_simplegoright(t_keymaster *lock, t_stockap *pac);
void		ft_goleft(t_keymaster *lock, t_stockap *pac);
int			ft_basic(t_stock *stock, t_stockap *pac, t_basiks *tools);
void		ft_rebasic(t_stockap *pac, t_basiks *tools);
int			ft_activkey(t_keymaster *lock, t_stockap *pac, t_stock *stock, t_basiks	*tools);

#endif