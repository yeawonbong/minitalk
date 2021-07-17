#include "minitalk.h"

static int	g_spid;
static int	g_byte; //8bit
static int	g_idx;
static int	g_count;

void	send_end(void)
{
	int i;

	i = 8;
	while (i--)
		kill(g_spid, SIGUSR1);
}

void	ft_send_number(int signo)
{
printf("GOT_SIGNAL\n");	
	if(g_count < 8)
	{
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
		}
		g_byte = g_byte >> 1;
		g_count++;
		return ;
	}
	g_idx++;
	printf("EXIT\n");
	send_end();
	exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
	struct sigaction sig1;

	g_byte = (int)argv[2][g_idx];
	printf("first g_byte : %d\n", g_byte);
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
	printf("넘버: %d\n", g_byte);
	while (argv[2][g_idx] && g_count < 8)
	{
	}
	return(0);
}