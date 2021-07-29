#ifndef MINITALK_H
# define MINITALK_H

# include "./libft/libft.h"
# include <unistd.h>
# include <signal.h>


/*
**	minitalk.c
*/
void		ft_send_signal(int pid, int signo);

/* 
**	client.c
*/
typedef struct s_client
{
	 int	count;
	 int	null; // flag to check if the string is over
}				t_client;

void		ft_disconnect(int signo);
void		ft_send_number(int signo, siginfo_t *siginfo, void *none);

/* 
**	server.c
*/
typedef struct s_server
{
	int	nextclient;
	int	currclient; // 전역 구조체 변수로 만들기
	int	byte;
	int	add;
	int	ret;
}				t_server;
t_server	ft_init(t_server server);
t_server	ft_connect(int pid, t_server server);
void		ft_server(int signo, siginfo_t *siginfo, void *none);

#endif

