#include "./include/client.h"

void	ft_disconnect(int signo)
{
	signo++;
	ft_putstr_fd("\nSent all the signals, Disconnected!\n", STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}

void	ft_send_number(int spid, char *argv[])
{
	// printf("GOT_SIGNAL\n");
	// printf("넘버: %d\n", g_client.byte);
	// printf("g_client.byte : %d, %d\n", g_client.byte, g_client.byte & 1);

	// printf("-----------SENT %d\n", g_client.byte & 1);
	int i;
	int	byte;
	int	count;

	i = 0;
	while(argv[2][i])
	{
		count = 0;
		byte = argv[2][i];
		while(count < 8)
		{
			// printf("to_send: %d\n", byte);
			kill(spid, (byte & 1) + TO_SIGNAL);
	// printf("-----------SENT %d\n", byte & 1);

			usleep(1000);
			byte = byte >> 1;
			count++;
		}
		i++;
	}
	// printf("ENDS\n");
	i = 8;
	while(0 < i--)
	{
		kill(spid, SIGUSR1);
		usleep(1000);
		// printf("SNED NULL\n");
	}
	return ;	
}

int main(int argc, char *argv[])
{
	// printf("-----------------------------char ptr : %c\n", *g_client.ptr);

	if (argc != 3)
	{
		ft_putstr_fd("Error : Invalid Input\n", STDOUT_FILENO);
		exit(EXIT_FAILURE);
	}
	ft_send_number(ft_atoi(argv[1]), argv);
	signal(SIGUSR2, &ft_disconnect);
	// pause();
	while (1)
	{
	}
	return(0);
}