#include "minitalk.h"

static char *g_ptr;
static int	g_spid;
static int	g_byte; //8bit
static int	g_count;
static int	g_null;

void	ft_disconnect()
{
	ft_putstr_fd("\nSent all the signals, Disconnected!\n", STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}

// void	send_end(void)
// {
// 	int i;
// printf("SEND_END\n");
// 	i = 8;
// 	while (i--)
// 		kill(g_spid, SIGUSR1);
// }

void	ft_send_number(int signo)
{
	// static int g_byte;
printf("GOT_SIGNAL\n");
	printf("넘버: %d\n", g_byte);

	// if(g_count < 8)
	// {
		printf("g_byte : %d, %d\n", g_byte, g_byte & 1);
		if (g_byte & 1)
		{
			kill(g_spid, SIGUSR2);
			printf("-----------SENT 1\n");
		}
		else if ((g_byte & 1) == 0)
		{
			kill(g_spid, SIGUSR1);
			printf("-----------SETNT 0\n");
		}//축약가능
		g_byte = g_byte >> 1;
		g_count++;
	// }
	if (g_count == 8)
	{
		if (!g_null)
		{
			if (*(g_ptr + 1))
			{
				g_byte = *(++g_ptr);
				printf("-----------------------------char ptr : %c\n", *g_ptr);
			}
			else
			{
				g_byte = 0;
				g_null = 1;
				printf("-----------------------------SET_NULL\n");
			}
			g_count = 0;
			return ;
		}
		ft_disconnect();
	}
	printf("나감\n");
	return ;
}

int main(int argc, char *argv[])
{
	struct sigaction sig1;

	g_ptr = argv[2];
	g_byte = *g_ptr;
	printf("first g_byte : %d\n", g_byte);
	printf("TEST ptr : %c\n", *g_ptr);

	if (argc != 3)
	{
		ft_putstr_fd("Error : Invalid Input\n", STDOUT_FILENO);
		exit(EXIT_FAILURE);
	}
	if (!g_spid)
	{
		g_spid = ft_atoi(argv[1]);
		kill(g_spid, SIGUSR1); // 처음 연결확인 signal
	}
	printf("my pid : %d\n", getpid());
	signal(SIGUSR1, &ft_send_number);
	// signal(SIGUSR2, &ft_disconnect);
	// printf("넘버: %d\n", g_byte);
	while (1)
	{
		// if (!*g_ptr)
		// {
		// 	printf("EXIT\n");
		// 	send_end();
		// }
	}
	return(0);
}