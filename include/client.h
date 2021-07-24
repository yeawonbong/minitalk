#ifndef CLIENT_H
# define CLIENT_H
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

# define TO_SIGNAL 30

typedef struct s_client
{
	 char *ptr;
	 int	spid;
	 int	byte; //8bit
	 int	count;
	 int	null; // flag to check if the string is over
}				t_client;
#endif