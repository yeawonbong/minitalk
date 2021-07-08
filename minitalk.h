#ifndef MINITALK_H
# define MINITALK_H
/*
**	temp header
*/
# include <stdio.h>
/*
**	end of temp
*/

# include "./libft/libft.h"
# include <unistd.h>
# include <signal.h>

struct sigaction
{
	void		(*sa_handler)(int);
	sigset_t	sa_mask;
	int			sa_flags;
};
#endif