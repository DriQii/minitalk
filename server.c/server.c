#include "server.h"


void	ft_handler(int sig, siginfo_t *siginfo, void *s);

int	main(void)
{
	int					pid;
	struct sigaction	sa;

	sa.sa_sigaction = ft_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	pid = (int)getpid();
	ft_printf("PID = %d\n", pid);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while(1);
	return(0);
}
void	ft_add_char(char c)
{
	static char	*str;
	static int	i;
	char		*newstr;
	char		*tmp;

	if (!str)
		str = ft_calloc(sizeof(char), 1);
	newstr = ft_calloc(sizeof(char), ft_strlen(str) + 2);
	ft_strcpy(newstr, str);
	tmp = str;
	str = newstr;
	free(tmp);
	str[i] = c;
	i++;
	if (c == 0)
	{
		ft_putstr(str);
		free(str);
	}
}

void	ft_handler(int sig, siginfo_t *siginfo, void *s)
{
	static int i;
	static int bit;

	(void)s;
	if(sig == SIGUSR1)
	{
		bit = bit | 1 << (7 - i);
		i++;
	}
	else
		i++;
	if(i == 8)
	{
		ft_add_char(bit);
		i = 0;
		bit = 0;
	}
	usleep(100);
	kill(siginfo->si_pid, SIGUSR1);
}
