#include "minitalk.h"

int main(int argc, char *argv[])
{
	int spid;
	int cpid;

	// spid = atoi(argv[1];
	if (argc != 3)
		exit(EXIT_FAILURE);
	cpid = getpid();
	kill(ft_atoi(argv[1]), SIGUSR1);
	printf("my pid : %d\n", cpid);
	printf("binary in bit : %d\n", cpid & 1);
	return(0);
}