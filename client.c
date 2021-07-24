#include "./include/client.h"

static t_client g_client;

void	ft_disconnect(int signo)
{
	signo++;
	ft_putstr_fd("Sent all the signals, Disconnected!\n", STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}

void	ft_send_number(int signo)
{
	usleep(50);
	kill(g_client.spid, (g_client.byte & 1) + signo); //signo (30)
	g_client.byte = g_client.byte >> 1;
	g_client.count++;
	if (g_client.count < 8)
		return ;
	else if (!g_client.null) //8번째일 때
	{
		if (*(g_client.ptr + 1)) // 다음 byte
			g_client.byte = *(++g_client.ptr);
		else //null 보내려고 
		{
			g_client.byte = 0;
			g_client.null = 1; //얘를 지금 잠시 주석해놨음.
		}
		g_client.count = 0;
		return ;
	}
	while(1)
		signal(SIGUSR2, &ft_disconnect);
}

int main(int argc, char *argv[])
{
	g_client.ptr = argv[2];
	g_client.byte = *g_client.ptr;
	if (argc != 3)
	{
		ft_putstr_fd("Error : Invalid Input\n", STDOUT_FILENO);
		exit(EXIT_FAILURE);
	}
	if (!g_client.spid)
	{
		g_client.spid = ft_atoi(argv[1]);
		usleep(50);
		kill(g_client.spid, SIGUSR1); // 처음 연결확인 signal
	}
	while (1)
	{
		signal(SIGUSR1, &ft_send_number);
		signal(SIGUSR2, &ft_disconnect);
	}
	return(0);
}