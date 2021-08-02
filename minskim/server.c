/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybong <ybong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 23:19:49 by ybong             #+#    #+#             */
/*   Updated: 2021/07/30 11:37:48 by ybong            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minitalk.h"

t_server	ft_init(t_server server)
{
	server.byte = 0;
	server.add = 1;
	server.ret = 0;
	return (server);
}

t_server	ft_connect(int pid, t_server server)
{
	server.currclient = pid;
	ft_putstr_fd("Successfully Connected!\nClient PID : ", STDOUT_FILENO);
	ft_putnbr_fd(server.currclient, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	server = ft_init(server);
	ft_send_signal(server.currclient, SIGUSR1);
	return (server);
}

t_server	ft_end_of_byte(t_server server)
{
	if (server.byte)
	{
		ft_putchar_fd(server.byte, STDOUT_FILENO);
		server = ft_init(server);
	}
	else
	{
		ft_putstr_fd("\nGot all the signals, Disconnected!\n", STDOUT_FILENO);
		ft_send_signal(server.currclient, SIGUSR2);
		if (server.nextclient)
		{
			server = ft_connect(server.nextclient, server);
			server.nextclient = 0;
		}
		else
			server.currclient = 0;
		server.ret = 1;
	}
	return (server);
}

void	ft_server(int signo, siginfo_t *siginfo, void *none)
{
	static t_server	server;

	none++;
	if (!server.currclient)
	{
		server = ft_connect(siginfo->si_pid, server);
		return ;
	}
	if (siginfo->si_pid != server.currclient)
	{
		if (!server.nextclient)
			server.nextclient = siginfo->si_pid;
		return ;
	}
	server.byte += server.add * (signo - 30);
	server.add *= 2;
	if (server.add == 256)
	{
		server = ft_end_of_byte(server);
		if (server.ret)
			return ;
	}
	ft_send_signal(server.currclient, SIGUSR1);
	return ;
}

int	main(void)
{
	static struct sigaction	server;

	server.sa_sigaction = ft_server;
	server.sa_flags = SA_SIGINFO;
	ft_putstr_fd("Server Launched! PID : ", STDOUT_FILENO);
	ft_putnbr_fd(getpid(), STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	while (1)
	{
		sigaction(SIGUSR1, &server, NULL);
		sigaction(SIGUSR2, &server, NULL);
	}
}
