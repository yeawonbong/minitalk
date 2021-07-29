/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybong <ybong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 23:27:31 by ybong             #+#    #+#             */
/*   Updated: 2021/07/29 23:27:32 by ybong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minitalk.h"

static char	*g_ptr;

void	ft_disconnect(int signo)
{
	signo++;
	ft_putstr_fd("Sent all the signals, Disconnected!\n", STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}

void	ft_send_number(int signo, siginfo_t *siginfo, void *none)
{
	static t_client	client;

	none++;
	ft_send_signal(siginfo->si_pid, (*g_ptr & 1) + signo);
	*g_ptr = *g_ptr >> 1;
	client.count++;
	if (client.count < 8)
		return ;
	if (!client.null)
	{
		if (*(g_ptr + 1))
			g_ptr++;
		else
			client.null = 1;
		client.count = 0;
	}
	while (client.null && client.count == 8)
		signal(SIGUSR2, &ft_disconnect);
	return ;
}

int	main(int argc, char *argv[])
{
	static struct sigaction	client;

	client.sa_sigaction = ft_send_number;
	client.sa_flags = SA_SIGINFO;
	g_ptr = argv[2];
	if (argc != 3)
	{
		ft_putstr_fd("Error : Invalid Input\n", STDOUT_FILENO);
		exit(EXIT_FAILURE);
	}
	ft_send_signal(ft_atoi(argv[1]), SIGUSR1);
	while (1)
		sigaction(SIGUSR1, &client, NULL);
	return (0);
}
