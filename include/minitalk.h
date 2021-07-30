/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybong <ybong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 02:10:09 by ybong             #+#    #+#             */
/*   Updated: 2021/07/30 11:38:10 by ybong            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

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
	 int	null;
}				t_client;

void		ft_disconnect(int signo);
void		ft_send_number(int signo, siginfo_t *siginfo, void *none);

/* 
**	server.c
*/
typedef struct s_server
{
	int	nextclient;
	int	currclient;
	int	byte;
	int	add;
	int	ret;
}				t_server;

t_server	ft_init(t_server server);
t_server	ft_connect(int pid, t_server server);
void		ft_server(int signo, siginfo_t *siginfo, void *none);

#endif
