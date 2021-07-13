#include "minitalk.h"

void	send_end(int spid)
{
	int i;

	i = 8;
	while (i--)
		kill(spid, SIGUSR1);
}

void	send_number(int spid, int num)
{
	int	temp;
	int	len;

	temp = num;
	len = 1;
	// while (temp && (temp /= 10))
	// 	len++;
	// printf("len is %d\n", len);
	while(num)
	{
		if (num & 1)
		{
			kill(spid, SIGUSR2);
			printf("SENT 1\n");
		}
		else
		{
			kill(spid, SIGUSR1);
			printf("SETNT 0\n");
		}
		num = num >> 1;
		// printf("shifted num : %d\n", num);
	}
}


int main(int argc, char *argv[])
{
	int spid;
	int cpid;

	spid = atoi(argv[1]);
	if (argc != 3)
		exit(EXIT_FAILURE);
	cpid = getpid();
	kill(ft_atoi(argv[1]), SIGUSR1);
	printf("my pid : %d\n", cpid);
	printf("binary in bit : %d\n", 1 | 0);
	send_number(spid, 10);
	return(0);
}