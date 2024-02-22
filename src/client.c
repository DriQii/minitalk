#include "minitalk.h"

int	state;

void	ft_putbit(char c, int pid)
{
	int 	i;

	i = 128;
	while (i > 0)
	{
		while (!state);
        usleep(100);
		if(c / i >= 1)
		{
			kill(pid, SIGUSR1);
			c = c % i;
		}
		else
			kill(pid, SIGUSR2);
		i /= 2;
		state = 0;
	}
}
void	ft_handler(int	sig)
{
	if(sig == SIGUSR1)
	{
		printf("Accuse de reception recu\n");
		state = 1;
	}
}

int	main(int argc, char **argv)
{
	int		server_pid;
	int		i;
	char	*str;

	state = 1;
	i = 0;
	server_pid = ft_atoi(argv[1]);
	str = argv[2];
	signal(SIGUSR1, ft_handler);
	while (str[i])
	{
		ft_putbit(str[i], server_pid);
		i++;
	}
	if(!str[i])
	{
		ft_putbit(str[i], server_pid);
		exit(0);
	}

}