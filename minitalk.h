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

# define SIG1 30
# define SIG2 31

typedef struct s_minitalk
{
	int	spid;
	int	cpid;
	
}				t_minitalk;
#endif