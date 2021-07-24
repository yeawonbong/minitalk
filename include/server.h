#ifndef SERVER_H
# define SERVER_H
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

typedef struct s_server
{
	struct sigaction connect;
	// sigset_t	block_mask;
	int	currclient; // 전역 구조체 변수로 만들기
	int	count;
	int	byte;
	int	add;
}				t_server;
#endif